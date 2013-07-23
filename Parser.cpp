#include "Parser.h"
#include "function.h"
#include "Error.h"

Parser::Parser():lexer(NULL)
{

}

Parser::Parser(Lexer* lexer):lexer(lexer),fileManager(0),scriptMgr(0)
{
	fileManager = fileManager->Instance();
	scriptMgr = scriptMgr->Instance();
}

void Parser::Move()
{
	look = lexer->ScanWord();
}

void Parser::Retrack(int num)
{
	look = lexer->RetrackWord(num);
}

void Parser::Match(int t, int id)
{
	if (look == NULL)
		return ;

	if (look->tag == t)
	{
		Move();
	}
	else
	{
		switch (id)
		{
		case ERR_BRACE: Error("大括号匹配错误，请检查是否缺少'{'或'}'"); break;
		case ERR_SCRIPT_TYPE: Error("脚本类型不匹配"); break;
		case ERR_ASSIGN: Error("等号后面应该接数据"); break;
		case ERR_PARENT: Error("括号匹配错误，请检查是否缺少'（'或'）'"); break;
		case ERR_SEMICN: Error("请检查行尾是否缺少';'"); break;
		default: Error("未知错误=_=!");break;
		}

		exit(1);
	}
}

void Parser::Error(string e)
{
	cout << "Error in Line" + IntToString(lexer->line) + " : " + e << endl;
}

void Parser::ScriptType()
{
	Match(LBRACE, ERR_BRACE);				// 左括号

	Varible();						// 分析头部变量声明
	while (FuncHeader() != 0)		// 函数头分析
	{
		Block();					// 分析程序块
	}

	Match(RBRACE, ERR_BRACE);
}

void Parser::ScriptAnalysis()
{
	// 创建新的脚本数据
	THScript* scriptData = new THScript();
	scriptData->fileName = fileManager->fileName;
	scriptMgr->AddTHScript(scriptData);
	scriptMgr->lastScript->symRoot = new SymbolTable(NULL);		// 新建符号表
	symTop = scriptMgr->lastScript->symRoot;

	ScriptHeader();					// 分析脚本头部声明，鉴定脚本类型
	ScriptType();					// 分析脚本类型及其内容
	
}

void Parser::ScriptHeader()
{
	Move();
	string str = look->ToString();
	string varStr = ((Word*)look)->lexeme;
	
	while (varStr[0] == '#')		// 读取脚本头部声明
	{
		Move();
		scriptMgr->lastScript->SetValue(varStr, look->ToString());
		Move();
		varStr = ((Word*)look)->lexeme;
	}


	if (scriptMgr->lastScript->touhouScript == "Stage")		// 验证主函数与脚本类型一致性
		Match(STAGEMAIN, ERR_SCRIPT_TYPE);
}

void Parser::Varible()
{
	
	while (look->tag == VARTK)
	{
		Move();

		while (look->tag != SEMICN) {
			if (look->tag == IDEN)	// 判断变量名
			{
				string symbolName, symbolType;
				double symbolValue = 0;
				int minusFlag = 0;

				symbolName = look->ToString();
				Move();

				if (look->tag == ASSIGN)
				{
					Move();

					if (look->tag == MINUS)
					{
						minusFlag = 1;
						Move();
					}

					if (look->tag == DOUBLECON)
					{
						symbolValue = atof(look->ToString().c_str());
					
					}
					Match(DOUBLECON, ERR_ASSIGN);
					
				}
				
				if (look->tag == COMMA)
				{
					Move();
				}

				if (minusFlag == 1)					// 正负判断
					symbolValue = -symbolValue;

				Symbol* symbol = new Symbol(symbolName, TYPE_DOUBLE, KIND_VAR, symbolValue);
				symTop->AddSymbol(symbol);
			}
		}

		Move();		// 跳过分号
	}
}

int Parser::FuncHeader()
{
	// 临时处理
	if (look->tag != RBRACE)
	{
		cout << "------" + look->ToString() + "------" << endl;
		Move();
		return 1;
	}
	else
	{
		return 0;
	}
	

	
}

Stmt* Parser::Block()
{
	Match(LBRACE, ERR_BRACE);

	// 建立下一层符号表并进入
	symTop = symTop->MakeNewSymbolTable();

	Stmt* stmt = Stmts();

	// 返回上一层符号表
	symTop = symTop->father;

	Match(RBRACE, ERR_BRACE);

	return stmt;
}

Stmt* Parser::Stmts()
{
	if (look->tag == RBRACE)
		return Stmt::Null;

	Stmt* first_stmt = StmtOne();
	Stmt* other_stmt = Stmts();

	return new Seq(first_stmt, other_stmt);
}

Stmt* Parser::StmtOne()
{
	Expr* expr;
	Stmt *l_stmt, *r_stmt;

	if (look->tag == RBRACE)
		return Stmt::Null;

	switch (look->tag)
	{
	case LBRACE:
		{
			return Block();
		}
	case SEMICN:
		{
			Move();
			return Stmt::Null;
		}
	case IFTK:
		{
			Move();
			Match(LPARENT, 3);
			
			expr = _bool();					// 读取判断条件

			Match(RPARENT, 3);

			if (look->tag == LBRACE)		// 判断执行内容
				l_stmt = Block();
			else 
				l_stmt = StmtOne();

			if (look->tag != ELSETK)
			{
				If* ifTemp = new If(expr, l_stmt);
				ifTemp->lexline = lexer->line;

				return ifTemp;
			}
			else
			{
				Move();
				
				if (look->tag == LBRACE)
					r_stmt = Block();
				else
					r_stmt = StmtOne();

				Else* elseTemp = new Else(expr, l_stmt, r_stmt);
			}
		}
	case VARTK:
		{
			Varible(); break;
		}
	default:
		{
			return Assign();
		}
	}
}

Stmt* Parser::Assign()
{
	Stmt* stmt = NULL;

	Symbol* symbol = symTop->GetSymbol(look->ToString());

	if (symbol == NULL)
	{
		Error("变量" + look->ToString() + "未定义");
	}

	Move();

	if (look->tag == ASSIGN)
	{
		Move();
		stmt = new Set(symbol->ToID(), _bool());
		stmt->lexline = lexer->line;
	}
	else
	{
		Error("表达式非法");
	}

	Match(SEMICN, ERR_SEMICN);

	return stmt;
}

Expr* Parser::_bool()
{
	Expr* expr = _join();

	while (look->tag == OR)
	{
		Token* tok = look;
		Move();
		expr = new Or(tok, expr, _join());
	}

	return expr;
}

Expr* Parser::_join()
{
	Expr* expr = _equality();

	while  (look->tag == AND)
	{
		Token* tok = look;
		Move();
		expr = new And(tok, expr, _equality());
	}

	return expr;
}

Expr* Parser::_equality()
{
	Expr* expr = _rel();

	if (expr == NULL)
		return expr;
	while (look->tag == EQL || look->tag == NEQ)
	{
		Token* tok = look;
		Move();
		expr = new Rel(tok, expr, _rel());
		expr->lexline = lexer->line;
	}

	return expr;
}

Expr* Parser::_rel()
{
	Expr* expr = _exprOne();

	if (expr == NULL)
		return expr;
	switch (look->tag)
	{
	case LSS: case LEQ: case GRE:case GEQ:
		{
			Token* tok = look;
			Move();
			expr = new Arith(tok, expr, _exprOne());
			expr->lexline = lexer->line;
		}
	default:
		return expr;
	}
}

Expr* Parser::_exprOne()
{
	Expr* expr = _term();

	if (expr == NULL)
		return expr;
	while (look->tag == PLUS || look->tag == MINUS)
	{
		Token* tok = look;
		Move();
		expr = new Arith(tok, expr, _term());
		expr->lexline = lexer->line;
	}

	return expr;
}

Expr* Parser::_term()
{
	Expr* expr = _unary();

	if (expr == NULL)
		return expr;
	while (look->tag == MULT || look->tag == DIV)
	{
		Token* tok = look;
		Move();
		expr = new Arith(tok, expr, _unary());
		expr->lexline = lexer->line;
	}

	return expr;
}

Expr* Parser::_unary()
{
	if (look->tag == MINUS)
	{
		Move();
		Unary* unary = new Unary(Word::minus, _unary());
		unary->lexline = lexer->line;
		return unary;
	} 
	else if (look->tag == PLUS)
	{
		Move();
		Unary* unary = new Unary(Word::plus, _unary());
		unary->lexline = lexer->line;
		return unary;
	}
	else if (look->tag == MINUSMINUS)
	{
		Move();
		Unary* unary = new Unary(Word::minusminus, _unary());
		unary->lexline = lexer->line;
		return unary;
	}
	else if (look->tag == PLUSPLUS)
	{
		Move();
		Unary* unary = new Unary(Word::plusplus, _unary());
		unary->lexline = lexer->line;
		return unary;
	}
	else if (look->tag == NOT)
	{
		Token* tok = look;
		Move();
		return new Not(tok, _unary());
	
	}
	else return _factor();
}

Expr* Parser::_factor()
{
	Expr* expr = NULL;
	switch (look->tag)
	{
	case LPARENT:
		{
			Move();
			expr = _bool();
			expr->lexline = lexer->line;
			Match(RPARENT, ERR_PARENT);
			return expr;
		}
	case DOUBLECON:
		{
			expr = new Constant(look, Type::Double);
			expr->lexline = lexer->line;
			Move();
			return expr;
		}
	case IDEN:
		{
			string name = look->ToString();
			
			Symbol* symTemp = symTop->GetSymbol(name);

			if (symTemp == NULL)
			{
				Error("变量" + name + "未定义");
			}

			Move();

			Id* idTemp = symTemp->ToID();
			return idTemp;
		}
	default:
		break;
	}

}
