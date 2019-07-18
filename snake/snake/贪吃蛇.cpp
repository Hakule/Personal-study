#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <process.h>
#include <stdio.h>


#define Max 100		//�ߵ�������

#define	up 72
#define	down 80
#define left 75
#define	right 77

typedef struct pointxy
{
	int x;
	int y;
}pointxy;

//��
struct Snake
{
	int lenth;			//�ߵĽ���
	pointxy xy[Max];	//����󳤶�
	char position;		//��Ƿ���
	int speed;			//�ߵ��ٶ�
}snake;


//ʳ��
struct Food
{
	pointxy foodxy;		//ʳ������
	int symbol;		//ʳ����ڱ�־
	int grade;			//����
}Food;

enum positon { sright, sleft, sup, sdown, paus}; //�ѷ����ж�ö��

/*���ú�������*/

void CreateMap();			//��ʼ����ͼ
void createsnake();			//��ʼ����
void drawsnake();			//�ߵĻ���
void SnakeMove();			//�ߵ��ƶ�
void KeyCommunity();		//���̽�������
void CreateFood();			//��ʼ��ʳ��
void drawfood();			//����ʳ��
void gameover();			//ֹͣ��Ϸ
void topic();				//���ɷ���
void grade();				//��ʾ����
void theme();				//��Ϸ�籾���Ѷȸ���
void GameEnd();				//��Ϸ��������
void HitWall();				//�ж��Ƿ�ײǽ
void EatFood();				//��ʳ��
void regame();				//���¿�ʼ��Ϸ

int main()
{
	initgraph(800, 650);
	topic();				//��ʾ����
	snake.speed = 200;
	setbkcolor(BLACK);
	cleardevice();
	createsnake();
	while (1)
	{
		cleardevice();		//ˢ���ߵ�·��
		CreateMap();
		grade();
		drawsnake();
		drawfood();
		theme();
		SnakeMove();
		if (Food.symbol == 0)
		{
			CreateFood();
		}
		Sleep(snake.speed);			//�����ߵ��ٶ�
		HitWall();
		EatFood();
	}

	_getch();
	closegraph();
	return 0;

}
//�滭��ͼ
void CreateMap()
{
	setlinecolor(COLORREF RGB(11, 191, 206));
	rectangle(90, 90, 510, 610);
	rectangle(100, 100, 500, 600);
}

//��ʼ����
void createsnake()
{
	snake.xy[2].x = 100;
	snake.xy[2].y = 100;

	snake.xy[1].x = 110;
	snake.xy[1].y = 100;

	snake.xy[0].x = 120;
	snake.xy[0].y = 100;

	snake.lenth = 3;
	snake.position = sright;

	Food.symbol = 0;

}

//�ߵĻ���(���ߵ��˶��������ʵ���ߵ��ƶ�)
void drawsnake()
{
	int i;
	for (i = 0; i < snake.lenth; i++)
	{
		setlinecolor(LIGHTCYAN);
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}

}

//�ߵ��˶�
void SnakeMove()
{
	int i, j;
	//���˵�һ������,��һ�������������ǰһ�ڵ�����
	for (i = snake.lenth - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	//��ͷ�˶�����,���ݷ����־���ƶ�
	switch (snake.position)
	{
	case sup:
		snake.xy[0].y -= 10;
		break;
	case sdown:
		snake.xy[0].y += 10;
		break;
	case sright:
		snake.xy[0].x += 10;
		break;
	case sleft:
		snake.xy[0].x -= 10;
		break;
	case paus:
		_getch();
		break;
	}
	while (_kbhit())
	{
		KeyCommunity();
	}
	//�ж���ײ���Լ�ʱ
	//����ͷ�����������ʱ,ײ���Լ�
	for (j = 2; j < snake.lenth; j++)
	{
		if (snake.xy[0].x == snake.xy[j].x && snake.xy[0].y == snake.xy[j].y)
			gameover();
	}
}


//�ж����Ƿ�ײǽ
void HitWall()
{
	if (snake.xy[0].x > 490 || snake.xy[0].x < 100 || snake.xy[0].y > 590 || snake.xy[0].y < 100)
	{
		gameover();		//ײǽʱ,��Ϸ����
	}
}

//�߳�ʳ�﹦��
void EatFood()
{
	if (snake.xy[0].x == Food.foodxy.x && snake.xy[0].y == Food.foodxy.y)
	{
		snake.lenth++;
		Food.grade += 10;
		Food.symbol = 0;
	}
}

//������������
void KeyCommunity()
{
	char key = _getch();

	switch (key)
	{
	case up:
		//ʵ���ߵ��ƶ��߼��ж�,�������෴�ķ����ƶ�
		if (snake.position != sdown)
			snake.position = sup;
		break;
	case down:
		if (snake.position != sup)
			snake.position = sdown;
		break;
	case left:
		if (snake.position != sright)
			snake.position = sleft;
		break;
	case right:
		if (snake.position != sleft)
			snake.position = sright;
		break;
	case 'p':
			snake.position = paus;
			break;
	}		
}

//��ʼ��ʳ��
void CreateFood()
{
	int i, x, y;
	srand((unsigned int)time(NULL));
	x = rand() % 40 + 10;	//��ʼ��ʳ������,ҪΪ10�ı���,�����޷�����
	y = rand() % 50 + 10;
	Food.foodxy.x = x * 10;
	Food.foodxy.y = y * 10;
	Food.symbol = 1;

	//ʳ�ﲻ�������ص�
	for (i = 0; i < snake.lenth; i++)
	{
		if (Food.foodxy.x == snake.xy[i].x && Food.foodxy.y == snake.xy[i].y)
		{
			x = rand() % 40 + 10;	//��������һ��ʳ��
			y = rand() % 50 + 10;
			Food.foodxy.x = x * 10;
			Food.foodxy.y = y * 10;
		}
	}
}

//����ʳ��
void drawfood()
{
	setfillcolor(COLORREF RGB(255, 0, 128));
	solidrectangle(Food.foodxy.x, Food.foodxy.y, Food.foodxy.x + 10, Food.foodxy.y + 10);
}

//��ʾ����

void grade()
{
	char player_grade[] = "��ǰ����";
	char player_speed[] = "��ǰ����";
	char grades[100];
	char speed[50];
	sprintf(grades, "%d", Food.grade);
	sprintf(speed, "%d", snake.speed);
	outtextxy(530, 100, player_grade);	//�����Ͻǽ�����ʾ����
	outtextxy(530, 400, player_speed);	//�����½ǽ�����ʾ�ٶ�
	outtextxy(530, 200, "����˵��");
	outtextxy(530, 225, "ʹ�÷��������");
	outtextxy(530, 250, "p����ͣ,������������");
	outtextxy(635, 100, grades);
	outtextxy(635, 400, speed);

}

//���ݷ����ݽ����鲢����Ѷ�
void theme()
{
	char type[15][20] = { "��Ӱ��", "������", "������", "��������", "�綾��", "������", "������", "�ʺ���", "������", "������", "�����", "������", "ʱ����", "��������", "[error:����ɾ��]" };
	char topic[15][200] = { "������ֻ��һ�����壬Ʈ���������С�", "�㻹��һ�������õ����֣�ëë�档", "��ֻ����ˮ���ﷴ���Ĵ���ˮ����", "����ж�������һ����״��������һ�ſ�����Ϊ��ʼ��", "��������̺��Ŵ����Ķ��أ�׼ȷ��˵������һ�����ߡ�", "�����λ���д�Ƥ�����Ϸ��ϣ�˿�����š�", "�㿪ʼע�⵽�Լ������������ɫ�ˡ�", "�����ϵ���ɫ���Խ�������ˣ���������һ̽������", "�㷢���Լ��������ɫ������Ϊ���������ڵ���������˹��ϡ�", "��͵͵��������������������޸����Լ�����ݡ�", "��ʡ�����߳��Ľ������裬����������������ɵİ��裬�����������������", "�������޸����������磬�������ǽ�����������������Ȩ����������", "���������ǰ��������߱������е�ʱ���ߣ�ֻΪ���м�ȡ����һ˿���֡�", "�����ڳ�Ϊ��������Ҫ��Ϊ�Ĵ��ڣ�������ʲô�����أ��������ʵ��Լ���", "�㲻����Ҫ�������������Լ�������ζ�ֻ��һ��������ɾ���˹����Լ���һ�У�������ֻ�뾲���أ��ȴ�ĩ�յĵ�����", };
	switch (Food.grade / 10)
	{
	case 0:	outtextxy(150, 30, type[0]);
		outtextxy(150, 55, topic[0]);
		setfillcolor(LIGHTGRAY);			//ʵ�ָ�����������ɫ
		break;
	case 1: outtextxy(150, 30, type[1]);
		outtextxy(150, 55, topic[1]);
		setfillcolor(COLORREF RGB(114, 233, 200));
		snake.speed = 120;
		break;
	case 2: outtextxy(150, 30, type[2]);
		outtextxy(150, 55, topic[2]);
		setfillcolor(COLORREF RGB(39, 247, 252));
		snake.speed = 120;
		break;
	case 3: outtextxy(150, 30, type[3]);
		outtextxy(150, 55, topic[3]);
		setfillcolor(COLORREF RGB(252, 44, 60));
		snake.speed = 110;
		break;
	case 4: outtextxy(150, 30, type[4]);
		outtextxy(150, 55, topic[4]);
		setfillcolor(COLORREF RGB(173, 200, 91));
		snake.speed = 110;
		break;
	case 5: outtextxy(150, 30, type[5]);
		outtextxy(150, 55, topic[5]);
		setfillcolor(COLORREF RGB(231, 240, 51));
		snake.speed = 100;
		break;
	case 6: outtextxy(150, 30, type[6]);
		outtextxy(150, 55, topic[6]);
		setfillcolor(COLORREF RGB(105, 182, 186));
		snake.speed = 100;
		break;
	case 7: outtextxy(150, 30, type[7]);
		outtextxy(150, 55, topic[7]);

		snake.speed = 100;
		break;
	case 8: outtextxy(150, 30, type[8]);
		outtextxy(150, 55, topic[8]);
		setfillcolor(COLORREF RGB(254, 254, 254));
		snake.speed = 90;
		break;
	case 9: outtextxy(150, 30, type[9]);
		outtextxy(150, 55, topic[9]);
		setfillcolor(COLORREF RGB(72, 251, 90));
		snake.speed = 90;
		break;
	case 10:outtextxy(150, 30, type[10]);
		outtextxy(150, 55, topic[10]);
		snake.speed = 85;
		break;
	case 11:outtextxy(150, 30, type[11]);
		outtextxy(150, 55, topic[11]);
		snake.speed = 80;
		break;
	case 12:outtextxy(150, 30, type[12]);
		outtextxy(150, 55, topic[12]);
		snake.speed = 70;
		break;
	case 13:outtextxy(150, 30, type[13]);
		outtextxy(150, 55, topic[13]);
		snake.speed = 70;
		break;
	case 14:outtextxy(150, 30, type[14]);
		outtextxy(150, 55, topic[14]);
		snake.speed = 60;
		break;
	case 15:outtextxy(150, 30, type[15]);
		outtextxy(150, 55, topic[15]);
		snake.speed = 60;
		break;
	}

}


//��Ϸ����
void gameover()
{
	settextstyle(25, 0, "����");
	char end[] = "���Ļ�����,";
	char end1[] = "Ҳ����һ�������ĸ��á�";
	char tips[] = "�����������";
	outtextxy(530, 200, end);
	outtextxy(530, 250, tips);
	outtextxy(530, 225, end1);
	_getch();
	GameEnd();
}

//��ʾ���漰��������
void topic()
{
	char topic[] = "̰��������";
	char choice[2][50] = { "1.��Ϸģʽ(δ���)", "2.��Ϸ˵��(δ���)" };
	settextstyle(80, 0, "��������");
	settextcolor(COLORREF RGB(134, 235, 246));
	outtextxy(200, 125, topic);
	settextstyle(25, 0, "����");
	settextcolor(COLORREF RGB(144, 236, 194));
	outtextxy(150, 285, choice[0]);
	outtextxy(550, 285, choice[1]);
	_getch();
}

//��Ϸ��������
void GameEnd()
{
	cleardevice();
	char choose;
	char End[] = "����������ʧЧ";
	char reburn[] = "�Ƿ�������һ�����ߣ�(y || n)";
	settextstyle(40, 0, "΢���ź�");
	settextcolor(COLORREF RGB(134, 235, 246));
	outtextxy(100, 125, End);
	outtextxy(100, 175, reburn);
	settextstyle(25, 0, "����");
	settextcolor(COLORREF RGB(144, 236, 194));
	_getch();
	choose = _getch();
	switch (choose)
	{
	case 'y': regame();
	case 'n': exit(0);
	}
	_getch();
	exit(0);
}

void regame()				//���¿�ʼ��Ϸ
{
	snake.speed = 200;
	setbkcolor(BLACK);
	cleardevice();
	createsnake();
	while (1)
	{
		cleardevice();		//ˢ���ߵ�·��
		CreateMap();
		grade();
		drawsnake();
		drawfood();
		theme();
		SnakeMove();
		if (Food.symbol == 0)
		{
			CreateFood();
		}
		Sleep(snake.speed);			//�����ߵ��ٶ�
		HitWall();
		EatFood();
	}

	_getch();

}