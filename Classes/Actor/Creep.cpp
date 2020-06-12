#include"Creep.h"

bool Creep::init(const std::string& filename,
	const EDebuffType debufftype,
	const EAttackMode attackmode,
	const int HP,
	const int attack)
{
	if (!Sprite::initWithFile(filename))
		return false;
	else
	{
		setHP(HP);
		setAttack(attack);
		setAttackMode(attackmode);
		setAlreadyDead(false);//û����
		setReleaseDebuff(debufftype);//���˻�Լ�����ɵ�Debuff
		setAttackRadius(attackmode);
		return true;
	}
 }



Creep* Creep::create(const std::string& filename,
	const EDebuffType debufftype,
	const EAttackMode attackmode,
	const int HP,
	const int attack)
{
	Creep* creep = new Creep();
	if (creep && creep->init(filename, debufftype, attackmode, HP, attack))
	{
		creep->autorelease();
		return creep;
	}
	else
	{
		CC_SAFE_DELETE(creep);
		return nullptr;
	}
 }


