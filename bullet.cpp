

//���վ��û���ֱ��д�ӵ�������д�����ˣ���ͬ���������ǲ�ͬ��newBullet��moveBullet��ʽ 

//����.h�ļ��� 
Vector<Sprite*>allBullet;//�����ӵ���ÿһ���ӵ�����һ������ 
void newBullet(float t);
void moveBullet(float t);

//.cpp�� 
//�ƻ�����
//�����ӵ�����
this->schedule(schedule_selector(/**/::newBullet), 0.5);//ÿ0.5�����һ�� /*���ڵ���*/ 
this->schedule(schedule_selector(/**/::moveBullet), 0.1);//ÿ0.1���ƶ�һ�� 
//���� 
void newBullet(float t) {
	auto spWeapon = this->getChildByTag(/**/);//ʵ����knight��λ�ô����ӵ� 
	Sprite* bullet = Sprite::create("bullet.png");
	bullet->setPosition(spWeapon->getPosition());
	this->addChild(bullet);
	this->allBullet.pushBack(bullet);//�ŵ������ӵ��� 
}

//���������knignt�ƶ������Ϸ������ӵ� 
void moveBullet(float t) {
	for (int i = 0;i<allBullet.size();i++) 
	{
		auto nowbullet = allBullet.at(i);
		nowbullet->setPositionY(nowbullet->getPositionY() +  map->getMapSize().height/30);//���Ƶ�ͼ��1/30 
		if (nowbullet->getPositionY > Director::getInstance()->getWinSize().height) { 
			nowbullet->removeFromParent();
			allBullet.eraseObject(nowbullet);//Խ���Ƴ� 
			i--;
		}
	}
}

//���ж�������� 
void Warship::shoot(){
if(weaponType==1){
if(isScheduled(schedule_selector(/**/::newBullet1))){
//����1�Ѿ�����
return;
}
if(isScheduled(schedule_selector(/**/::newBullet1))){
//����ʱ����2�Ѿ�������Ҫ�ر�����2
unschedule(schedule_selector(Warship::newBullet2))
}
//ÿ0.3�뷢��һ�ι�������
schedule(schedule_selector(/**/::newBullet1),0.5);
schedule(schedule_selector(/**/::moveBullet),0.1);
} 
else if(weaponType==2){
if(isScheduled(schedule_selector(/**/::newBullet2))){
//����2�Ѿ�����
return;
}
if(isScheduled(schedule_selector(/**/::newBullet1))){
//����ʱ����2�Ѿ�������Ҫ�ر�����2
unschedule(schedule_selector(/**/::newBullet2))
}
schedule(schedule_selector(/**/::newBullet2),0.5);
schedule(schedule_selector(/**/::moveBullet),0.1);
} 

//������ײ��� 























