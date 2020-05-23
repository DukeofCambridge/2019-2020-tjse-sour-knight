#include"Knight.h"

//�ڶ���������װ����������������ʽ�����������ں󼸸��汾ʵ��
 bool Knight::init(const std::string& filename, const::String& equipment, EAttackMode attackmode)
{
     if (!Sprite::initWithFile(filename))
         return false;
     else
     {
         /*��ʿ��ɫ�ĳ�ʼ״̬Ϊ��
         HP��7
         Armor:6
         MP:200
         */

         setHP(HP_OF_KNIGHT);
         setArmor(ARMOR_OF_KNIGHT);
         setMP(MP_OF_KNIGHT);
         setAttackRadius(0);//�����뾶�д��ں�������
         setAttackTarget(nullptr);
         setAttackMode(attackmode);

     }
}


//�ڶ���������װ����������������ʽ�����������ں󼸸��汾ʵ��
 Knight* Knight::create(const std::string& filename, const::String& equipment, EAttackMode attackmode)
{
     Knight* knight = new Knight();
     if (knight && knight->init(filename, equipment, attackmode))
     {
         knight->autorelease;
         return knight;
     }
     CC_SAFE_DELETE(knight);
     return nullptr;
}

void skillOfKnight()//����ʵ�ֻ���������ʵ�ֺ����
{

}