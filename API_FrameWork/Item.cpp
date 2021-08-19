#include "framework.h"
#include "Item.h"

Item::Item()
{
	/*ITEMDATA item1;
	ZeroMemory(&item1, sizeof(Item));
	WEAPON_TYPE weapon_type;
	EQUIPTYPE equip_type;
	item1.item_image;
	item1.item_colbox;
	item1.item_name;
	item1.item_info;
	item1.item_shopInfo;
	item1.price = 0;
	item1.itemType;
	item1.equipHP = 0;
	item1.equipMaxHP = 0;
	item1.equipMP = 0;
	item1.equipMaxMP = 0;
	item1.equipSpeed = 0;
	item1.equipAtk = 0;
	item1.equipAtkSpeed = 0;
	item1.equipCritical = 0;
	item1.equipSkillPower = 0;
	item1.equipSkillCollTime = 0;*/
}

Item::~Item()
{
}

HRESULT Item::init()
{
	ITEMDATA item1;
	ZeroMemory(&item1, sizeof(Item));

	item1.item_image = new image;
	item1.item_image = IMAGE->addImage("�Ź�", "images/item/shoes.bmp", 19,23, true);
	item1.x = 470;
	item1.y = 400;
	item1.item_colbox = IMAGE->findImage("�Ź�")->getBoundingBox(item1.x, item1.y);
	item1.item_name = "�Ź�";
	item1.item_info = "�̵��ϱ� ���ϰ� ������� �Ź� �̵��ӵ��� �����Ѵ�";
	item1.item_shopInfo = "���밨�� ���� �Ź��̾�";
	item1.price = 80;
	item1.equip_type = EQUIPTYPE::boot;
	item1.itemType = ITEMTYPE::equip;
	item1.equipHP = 1;
	item1.equipMaxHP = 0;
	item1.equipMP = 0;
	item1.equipMaxMP = 0;
	item1.equipSpeed = 1;
	item1.equipAtk = 0;
	item1.equipAtkSpeed = 0;
	item1.equipCritical = 0;
	item1.equipSkillPower = 0;
	item1.equipSkillCollTime = 0;	

	ITEMDATA item2;
	ZeroMemory(&item2, sizeof(Item));

	item2.item_image = new image;
	item2.item_image = IMAGE->addImage("����ź", "images/item/wrongbullet.bmp", 26, 26, true);
	item2.x = 470;
	item2.y = 400;
	item2.item_colbox = IMAGE->findImage("����ź")->getBoundingBox(item2.x, item2.y);
	item2.item_name = "����ź";
	item2.item_info = "�Ϲݰ����� ����� 30% ���� ź���� 3�������� �߻�";
	item2.item_shopInfo = "��û�� �����̾� �� ��� ���� ��õ��";
	item2.price = 300;
	item2.itemType = ITEMTYPE::accesory;
	item2.equipHP = 0;
	item2.equipMaxHP = 0;
	item2.equipMP = 0;
	item2.equipMaxMP = 0;
	item2.equipSpeed = 0;
	item2.equipAtk = -PLAYERDATA->getDamage() * 0.3;
	item2.equipAtkSpeed = 0;
	item2.equipCritical = 0;
	item2.equipSkillPower = 0;
	item2.equipSkillCollTime = 0;
	//ź 3�� �������� �����


	ITEMDATA item3;
	ZeroMemory(&item3, sizeof(Item));

	item3.item_image = new image;
	item3.item_image = IMAGE->addImage("���ǿ��ǽ�", "images/item/winterdress.bmp", 22, 21, true);
	item3.x = 470;
	item3.y = 400;
	item3.item_colbox = IMAGE->findImage("���ǿ��ǽ�")->getBoundingBox(item3.x, item3.y);
	item3.item_name = "���� ���ǽ�";
	item3.item_info = "���ʳ��󿡼� �Դ� �� ���ǽ� ü���� �þ��";
	item3.item_shopInfo = "���� �������� ���� ���̾�";
	item3.price = 120;
	item3.itemType = ITEMTYPE::equip;
	item3.equip_type = EQUIPTYPE::armor;
	item3.equipHP = 2;
	item3.equipMaxHP = 0;
	item3.equipMP = 0;
	item3.equipMaxMP = 0;
	item3.equipSpeed = 0;
	item3.equipAtk = 0;
	item3.equipAtkSpeed = 0;
	item3.equipCritical = 0;
	item3.equipSkillPower = 10;
	item3.equipSkillCollTime = 0;

	ITEMDATA item4;
	ZeroMemory(&item4, sizeof(Item));

	item4.item_image = new image;
	item4.item_image = IMAGE->addImage("�����Ǹ�", "images/item/whisle.bmp", 26, 26, true);
	item4.x = 470;
	item4.y = 400;
	item4.item_colbox = IMAGE->findImage("�����Ǹ�")->getBoundingBox(item4.x, item4.y);
	item4.item_name = "����-�Ǹ�";
	item4.item_info ="����˻簡 �Ҵ� �Ǹ� ġ��Ÿ�� �����Ѵ�";
	item4.item_shopInfo ="�߽������ �˻簡 ���� �Ǹ��� ġ��Ÿ�� ������";
	item4.price = 120;
	item4.itemType = ITEMTYPE::accesory;
	item4.equipHP = 0;
	item4.equipMaxHP = 0;
	item4.equipMP = 0;
	item4.equipMaxMP = 0;
	item4.equipSpeed = 0;
	item4.equipAtk = 0;
	item4.equipAtkSpeed = 0;
	item4.equipCritical = 15;
	item4.equipSkillPower = 0;
	item4.equipSkillCollTime = 0;

	ITEMDATA item5;
	ZeroMemory(&item5, sizeof(Item));

	item5.item_image = new image;
	item5.item_image = IMAGE->addImage("�׵�", "images/item/wood_sword.bmp", 29, 31, true);
	item5.x = 470;
	item5.y = 400;
	item5.item_colbox = IMAGE->findImage("�׵�")->getBoundingBox(item5.x, item5.y);
	item5.item_name = "�׵�";
	item5.item_info = "�˼� �ܷ��� ���� �� 1õ ���� ������ '��'�̶� �ϰ�, 1������ ������ '��'�̶� �Ѵ�";
	item5.item_shopInfo = "�Ʒ��� ���ؼ� ���� ���� ���̾� ���� �̷��� ����..?";
	item5.price = 60;
	item5.itemType = ITEMTYPE::weapon;
	item5.weapon_type = WEAPON_TYPE::sword;
	item5.equipHP = 0;
	item5.equipMaxHP = 0;
	item5.equipMP = 0;
	item5.equipMaxMP = 0;
	item5.equipSpeed = 0;
	item5.equipAtk = 6;
	item5.equipAtkSpeed = 2;
	item5.equipCritical = 0;
	item5.equipSkillPower = -2;
	item5.equipSkillCollTime = 0;
	ITEMDATA item6;
	ZeroMemory(&item6, sizeof(Item));

	item6.item_image = new image;
	item6.item_image = IMAGE->addImage("�̻��ѳ����ǵ巹��", "images/item/aliceDress.bmp", 26, 24, true);
	item6.x = 470;
	item6.y = 400;
	item6.item_colbox = IMAGE->findImage("�̻��ѳ����ǵ巹��")->getBoundingBox(item6.x, item6.y);
	item6.item_name ="�̻��� ������ �巹��";
	item6.item_info ="�̻��� ���󿡼� �� �ҳడ �Դ� �� ��°������ �Ź̰� �鷯�ٴ´� ü���� �����ϰ� �̵��ӵ��� �����Ѵ�";
	item6.item_shopInfo = "��޽����� �������� ���̾�";
	item6.price = 200;
	item6.itemType = ITEMTYPE::equip;
	item6.equip_type = EQUIPTYPE::armor;
	item6.equipHP = 3;
	item6.equipMaxHP = 0;
	item6.equipMP = 0;
	item6.equipMaxMP = 0;
	item6.equipSpeed = 1;
	item6.equipAtk = 0;
	item6.equipAtkSpeed = 0;
	item6.equipCritical = 0;
	item6.equipSkillPower = 0;
	item6.equipSkillCollTime = 0;

	ITEMDATA item7;
	ZeroMemory(&item7, sizeof(Item));

	item7.item_image = new image;
	item7.item_image = IMAGE->addImage("�̻��ѳ����Ǻ���", "images/item/aliceboots.bmp", 20, 25, true);
	item7.x = 470;
	item7.y = 400;
	item7.item_colbox = IMAGE->findImage("�̻��ѳ����Ǻ���")->getBoundingBox(item7.x, item7.y);
	item7.item_name = "�̻��� ������ ����";
	item7.item_info = "�̻��� ���󿡼� �� �ҳడ �Դ� �Ź� ��°������ �Ź̰� �鷯�ٴ´� ���ݷ��� �����ϰ� �̵��ӵ��� �����Ѵ�.";
	item7.item_shopInfo= " ��޽����� �������� �Ź��̾�";
	item7.price = 200;
	item7.itemType = ITEMTYPE::equip;
	item1.equip_type = EQUIPTYPE::boot;
	item7.equipHP = 0;
	item7.equipMaxHP = 0;
	item7.equipMP = 0;
	item7.equipMaxMP = 0;
	item7.equipSpeed = 1;
	item7.equipAtk = 3;
	item7.equipAtkSpeed = 1;
	item7.equipCritical = 0;
	item7.equipSkillPower = 0;
	item7.equipSkillCollTime = 0;

	ITEMDATA item8;
	ZeroMemory(&item8, sizeof(Item));

	item8.item_image=new image;
	item8.item_image =  IMAGE->addImage("�ż�������", "images/item/holy_relric.bmp", 28, 24, true);
	item8.x = 470;
	item8.y = 400;
	item8.item_colbox = IMAGE->findImage("�ż�������")->getBoundingBox(item8.x, item8.y);
	item8.item_name = "�ż��� ����";
	item8.item_info = "�ż��� �������� ����-�ǿܷ� �������� ���԰��� ���ݷ��� �����ϰ� ���ݼӵ��� �����Ѵ� ";
	item8.item_shopInfo="��н����� ������� ������ �����̾� �췡?";
	item8.price = 200;
	item8.itemType = ITEMTYPE::accesory;
	item8.equipHP = 0;
	item8.equipMaxHP = 0;
	item8.equipMP = 0;
	item8.equipMaxMP = 0;
	item8.equipSpeed = 0;
	item8.equipAtk = 10;
	item8.equipAtkSpeed = 2;
	item8.equipCritical = 0;
	item8.equipSkillPower = 0;
	item8.equipSkillCollTime = 0;

	ITEMDATA item9;
	ZeroMemory(&item9, sizeof(Item));

	item9.item_image = new image;
	item9.item_image = IMAGE->addImage("��ġ��������", "images/item/halem.bmp", 24, 26, true);
	item9.x = 470;
	item9.y = 400;
	item9.item_colbox = IMAGE->findImage("��ġ��������")->getBoundingBox(item9.x, item9.y);
	item9.item_name = "��ġ���� ����";
	item9.item_info = "���پ��ִ� �����̴� ü���� ũ�� �����Ѵ�";
	item9.item_shopInfo = "������ ����� ������ ��� 'Succeeding you father'";
	item9.price = 300;
	item9.itemType = ITEMTYPE::equip;
	item9.equip_type = EQUIPTYPE::hat;
	item9.equipHP = 0;
	item9.equipMaxHP = 6;
	item9.equipMP = 0;
	item9.equipMaxMP = 0;
	item9.equipSpeed = -1;
	item9.equipAtk = 0;
	item9.equipAtkSpeed = 0;
	item9.equipCritical = 0;
	item9.equipSkillPower = 0;
	item9.equipSkillCollTime = 0;

	ITEMDATA item10;
	ZeroMemory(&item10, sizeof(Item));

	item10.item_image = new image;
	item10.item_image = IMAGE->addImage("�׹̳���", "images/item/seed.bmp", 28, 25, true);
	item10.x = 470;
	item10.y = 400;
	item10.item_colbox = IMAGE->findImage("�׹̳���")->getBoundingBox(item10.x, item10.y);
	item10.item_name ="�׹̳���";
	item10.item_info ="������� ��Ⱑ �ּ� �Ǿ��";
	item10.item_shopInfo="�ܱ����� ���ؿ� �Ĺ��̾� �װ����� �����ڶ�� �θ�����?";
	item10.price = 20;
	item10.itemType = ITEMTYPE::accesory;
	item10.equipHP = 0;
	item10.equipMaxHP = 0;
	item10.equipMP = 0;
	item10.equipMaxMP = 0;
	item10.equipSpeed = 0;
	item10.equipAtk = 0;
	item10.equipAtkSpeed = 0;
	item10.equipCritical = 0;
	item10.equipSkillPower = 0;
	item10.equipSkillCollTime = 0;

	ITEMDATA item11;
	ZeroMemory(&item11, sizeof(Item));

	item11.item_image = new image;
	item11.item_image = IMAGE->addImage("��ũŬ����", "images/item/darksword.bmp", 30, 30, true);
	item11.x = 470;
	item11.y = 400;
	item11.item_colbox = IMAGE->findImage("��ũŬ����")->getBoundingBox(item11.x, item11.y);
	item11.item_name = "��ũŬ����";
	item11.item_info = "������� ������ ����� ���� �Ұ�";
	item11.item_shopInfo = "������ ���ֿ� �ɸ��� ���̾� ���������� ��õ�� �����ʾ� ";
	item11.price = 300;
	item11.itemType = ITEMTYPE::weapon;
	item11.weapon_type = WEAPON_TYPE::sword;
	item11.equipHP = -2;
	item11.equipMaxHP = -2;
	item11.equipMP = 0;
	item11.equipMaxMP = 0;
	item11.equipSpeed = 0;
	item11.equipAtk = 30;
	item11.equipAtkSpeed = 3;
	item11.equipCritical = 0;
	item11.equipSkillPower = -6;
	item11.equipSkillCollTime = 0;

	ITEMDATA item12;
	ZeroMemory(&item12, sizeof(Item));

	item12.item_image = new image;
	item12.item_image = IMAGE->addImage("����", "images/item/pot_head.bmp", 28, 25, true);
	item12.x = 470;
	item12.y = 400;
	item12.item_colbox = IMAGE->findImage("����")->getBoundingBox(item12.x, item12.y);
	item12.item_name = "����";
	item12.item_info = "ü��+2";
	item12.item_shopInfo = "������ ���� ���Ѿ�";
	item12.price = 70;
	item12.itemType =ITEMTYPE::accesory;
	item12.equipHP = 0;
	item12.equipMaxHP = 2;
	item12.equipMP = 0;
	item12.equipMaxMP = 0;
	item12.equipSpeed = 0;
	item12.equipAtk = 0;
	item12.equipAtkSpeed = 0;
	item12.equipCritical = 0;
	item12.equipSkillPower = 0;
	item12.equipSkillCollTime = 0;

	ITEMDATA item13;
	ZeroMemory(&item13, sizeof(Item));

	item13.item_image = new image;
	item13.item_image = IMAGE->addImage("��庸��", "images/item/wood_bow.bmp", 24, 24, true);
	item13.x = 470;
	item13.y = 400;
	item13.item_colbox = IMAGE->findImage("��庸��")->getBoundingBox(item13.x, item13.y);
	item13.item_name="��庸��";
	item13.item_info ="������ ������ ���� Ȱ �v�� ��������� ź���� ���ϴ�";
	item13.item_shopInfo ="�� �������̾�... ������";
	item13.price = 60;
	item13.itemType = ITEMTYPE::weapon;
	item13.weapon_type = WEAPON_TYPE::bow;
	item13.equipHP = 0;
	item13.equipMaxHP = 0;
	item13.equipMP = 0;
	item13.equipMaxMP = 0;
	item13.equipSpeed = 0;
	item13.equipAtk = 3;
	item13.equipAtkSpeed = 1;
	item13.equipCritical = 0;
	item13.equipSkillPower = 0;
	item13.equipSkillCollTime = 0;

	ITEMDATA item14;
	ZeroMemory(&item14, sizeof(Item));

	item14.item_image = new image;
	item14.item_image = IMAGE->addImage("��纸��", "images/item/gold_bow.bmp", 24, 24, true);
	item14.x = 470;
	item14.y = 400;
	item14.item_colbox = IMAGE->findImage("��纸��")->getBoundingBox(item14.x, item14.y);
	item14.item_name="��纸��";
	item14.item_info="��! ���� �ְ��! �޴޵�! ������!";
	item14.item_shopInfo="�� ���� �̷��� ���°ɱ� �췡?";
	item14.price = 120;
	item14.itemType = ITEMTYPE::weapon;
	item14.weapon_type = WEAPON_TYPE::bow;
	item14.equipHP = 0;
	item14.equipMaxHP = 1;
	item14.equipMP = 0;
	item14.equipMaxMP = 0;
	item14.equipSpeed = 2;
	item14.equipAtk = 9;
	item14.equipAtkSpeed = 0;
	item14.equipCritical = 0;
	item14.equipSkillPower = 0;
	item14.equipSkillCollTime = 0;

	ITEMDATA item15;
	ZeroMemory(&item15, sizeof(Item));

	item15.item_image = new image;
	item15.item_image = IMAGE->addImage("����������", "images/item/wood_staff.bmp", 24, 24, true);
	item15.x = 470;
	item15.y = 400;
	item15.item_colbox = IMAGE->findImage("����������")->getBoundingBox(item15.x, item15.y);
	item15.item_name = "���� ������";
	item15.item_info = "����� ���������� �������� ������ �����ش�";
	item15.item_shopInfo = "���� �ִ� �����̾� �Ҿ�������� �ƴϰ���...?";
	item15.price = 60;
	item15.itemType = ITEMTYPE::weapon;
	item15.weapon_type = WEAPON_TYPE::staff;
	item15.equipHP = 0;
	item15.equipMaxHP = 0;
	item15.equipMP = 0;
	item15.equipMaxMP = 1;
	item15.equipSpeed = 0;
	item15.equipAtk = 0;
	item15.equipAtkSpeed = 0;
	item15.equipCritical = 0;
	item15.equipSkillPower = 1;
	item15.equipSkillCollTime = 0;
	
	
	_vItem.push_back(item1);
	_vItem.push_back(item2);
	_vItem.push_back(item3);
	_vItem.push_back(item4);
	_vItem.push_back(item5);
	_vItem.push_back(item6);
	_vItem.push_back(item7);
	_vItem.push_back(item8);
	_vItem.push_back(item9);
	_vItem.push_back(item10);
	_vItem.push_back(item11);
	_vItem.push_back(item12);
	_vItem.push_back(item13);
	_vItem.push_back(item14);
	_vItem.push_back(item15);



	return S_OK;

}

void Item::release()
{
}

void Item::update()
{
}

void Item::render()
{
}


void Item::removeitem(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}
