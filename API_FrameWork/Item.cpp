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
	item1.item_image = IMAGE->addImage("신발", "images/item/shoes.bmp", 19,23, true);
	item1.x = 470;
	item1.y = 400;
	item1.item_colbox = IMAGE->findImage("신발")->getBoundingBox(item1.x, item1.y);
	item1.item_name = "신발";
	item1.item_info = "이동하기 편리하게 만들어진 신발 이동속도가 증가한다";
	item1.item_shopInfo = "착용감이 편한 신발이야";
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
	item2.item_image = IMAGE->addImage("오발탄", "images/item/wrongbullet.bmp", 26, 26, true);
	item2.x = 470;
	item2.y = 400;
	item2.item_colbox = IMAGE->findImage("오발탄")->getBoundingBox(item2.x, item2.y);
	item2.item_name = "오발탄";
	item2.item_info = "일반공격의 대미지 30% 감소 탄약을 3방향으로 발사";
	item2.item_shopInfo = "엄청난 유물이야 꼭 사는 것을 추천해";
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
	//탄 3개 나가도록 만들기


	ITEMDATA item3;
	ZeroMemory(&item3, sizeof(Item));

	item3.item_image = new image;
	item3.item_image = IMAGE->addImage("눈의원피스", "images/item/winterdress.bmp", 22, 21, true);
	item3.x = 470;
	item3.y = 400;
	item3.item_colbox = IMAGE->findImage("눈의원피스")->getBoundingBox(item3.x, item3.y);
	item3.item_name = "눈의 원피스";
	item3.item_info = "북쪽나라에서 입는 롱 원피스 체력이 늘어난다";
	item3.item_shopInfo = "좋은 원단으로 만든 옷이야";
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
	item4.item_image = IMAGE->addImage("관악피리", "images/item/whisle.bmp", 26, 26, true);
	item4.x = 470;
	item4.y = 400;
	item4.item_colbox = IMAGE->findImage("관악피리")->getBoundingBox(item4.x, item4.y);
	item4.item_name = "관악-피리";
	item4.item_info ="어느검사가 불던 피리 치명타가 증가한다";
	item4.item_shopInfo ="야스오라는 검사가 놓고간 피리야 치명타가 증가해";
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
	item5.item_image = IMAGE->addImage("죽도", "images/item/wood_sword.bmp", 29, 31, true);
	item5.x = 470;
	item5.y = 400;
	item5.item_colbox = IMAGE->findImage("죽도")->getBoundingBox(item5.x, item5.y);
	item5.item_name = "죽도";
	item5.item_info = "검술 단련을 위한 검 1천 일의 연습을 '단'이라 하고, 1만일의 연습을 '련'이라 한다";
	item5.item_shopInfo = "훈련을 위해서 많이 쓰는 검이야 설마 이런거 쓰니..?";
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
	item6.item_image = IMAGE->addImage("이상한나라의드레스", "images/item/aliceDress.bmp", 26, 24, true);
	item6.x = 470;
	item6.y = 400;
	item6.item_colbox = IMAGE->findImage("이상한나라의드레스")->getBoundingBox(item6.x, item6.y);
	item6.item_name ="이상한 나라의 드레스";
	item6.item_info ="이상한 나라에서 온 소녀가 입던 옷 어째서인지 거미가 들러붙는다 체력이 증가하고 이동속도가 증가한다";
	item6.item_shopInfo = "고급스러운 디자인의 옷이야";
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
	item7.item_image = IMAGE->addImage("이상한나라의부츠", "images/item/aliceboots.bmp", 20, 25, true);
	item7.x = 470;
	item7.y = 400;
	item7.item_colbox = IMAGE->findImage("이상한나라의부츠")->getBoundingBox(item7.x, item7.y);
	item7.item_name = "이상한 나라의 부츠";
	item7.item_info = "이상한 나라에서 온 소녀가 입던 신발 어째서인지 거미가 들러붙는다 공격력이 증가하고 이동속도가 증가한다.";
	item7.item_shopInfo= " 고급스러운 디자인의 신발이야";
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
	item8.item_image =  IMAGE->addImage("신성한유물", "images/item/holy_relric.bmp", 28, 24, true);
	item8.x = 470;
	item8.y = 400;
	item8.item_colbox = IMAGE->findImage("신성한유물")->getBoundingBox(item8.x, item8.y);
	item8.item_name = "신성한 유물";
	item8.item_info = "신성시 여겨지는 유물-의외로 상점에서 구입가능 공격력이 증가하고 공격속도가 증가한다 ";
	item8.item_shopInfo="비밀스러운 방법으로 가져온 유물이야 살래?";
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
	item9.item_image = IMAGE->addImage("리치왕의투구", "images/item/halem.bmp", 24, 26, true);
	item9.x = 470;
	item9.y = 400;
	item9.item_colbox = IMAGE->findImage("리치왕의투구")->getBoundingBox(item9.x, item9.y);
	item9.item_name = "리치왕의 투구";
	item9.item_info = "얼어붙어있는 투구이다 체력이 크게 증가한다";
	item9.item_shopInfo = "왕위에 계승할 느낌이 들어 'Succeeding you father'";
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
	item10.item_image = IMAGE->addImage("테미나리", "images/item/seed.bmp", 28, 25, true);
	item10.x = 470;
	item10.y = 400;
	item10.item_colbox = IMAGE->findImage("테미나리")->getBoundingBox(item10.x, item10.y);
	item10.item_name ="테미나리";
	item10.item_info ="기분좋은 향기가 솔솔 피어난다";
	item10.item_shopInfo="외국에서 구해온 식물이야 그곳에선 모코코라고 부르던데?";
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
	item11.item_image = IMAGE->addImage("다크클라우드", "images/item/darksword.bmp", 30, 30, true);
	item11.x = 470;
	item11.y = 400;
	item11.item_colbox = IMAGE->findImage("다크클라우드")->getBoundingBox(item11.x, item11.y);
	item11.item_name = "다크클라우드";
	item11.item_info = "사용자의 생명을 뺏어가는 작은 소검";
	item11.item_shopInfo = "만지면 저주에 걸리는 검이야 강력하지만 추천은 하지않아 ";
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
	item12.item_image = IMAGE->addImage("냄뚜", "images/item/pot_head.bmp", 28, 25, true);
	item12.x = 470;
	item12.y = 400;
	item12.item_colbox = IMAGE->findImage("냄뚜")->getBoundingBox(item12.x, item12.y);
	item12.item_name = "냄뚜";
	item12.item_info = "체력+2";
	item12.item_shopInfo = "집에서 쓰던 냄뚜야";
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
	item13.item_image = IMAGE->addImage("우드보우", "images/item/wood_bow.bmp", 24, 24, true);
	item13.x = 470;
	item13.y = 400;
	item13.item_colbox = IMAGE->findImage("우드보우")->getBoundingBox(item13.x, item13.y);
	item13.item_name="우드보우";
	item13.item_info ="간단한 나무로 만든 활 쉡게 당겨지지만 탄성이 약하다";
	item13.item_shopInfo ="내 수제작이야... 웃지마";
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
	item14.item_image = IMAGE->addImage("골든보우", "images/item/gold_bow.bmp", 24, 24, true);
	item14.x = 470;
	item14.y = 400;
	item14.item_colbox = IMAGE->findImage("골든보우")->getBoundingBox(item14.x, item14.y);
	item14.item_name="골든보우";
	item14.item_info="금! 금이 최고야! 메달도! 성적도!";
	item14.item_shopInfo="왜 금을 이런데 쓰는걸까 살래?";
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
	item15.item_image = IMAGE->addImage("나무지팡이", "images/item/wood_staff.bmp", 24, 24, true);
	item15.x = 470;
	item15.y = 400;
	item15.item_colbox = IMAGE->findImage("나무지팡이")->getBoundingBox(item15.x, item15.y);
	item15.item_name = "나무 지팡이";
	item15.item_info = "평범한 나무지팡이 착용자의 마력을 높여준다";
	item15.item_shopInfo = "집에 있던 지팡이야 할어버지꺼는 아니겠지...?";
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
