#include "Object.h"

Object::Object()
{

}

Object::Object(THScriptFull* v_script)
{
	script = new THScript(*v_script);
}