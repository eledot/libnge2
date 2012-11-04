#include "libnge2.h"
#include "nge_app.hpp"
#include <stdio.h>

/**
 * ����ͼƬ��ʾ
 * ͬʱ��ΪC++ Style App������
 */

#ifdef ANDROID
#define RES_PATH(path) ("/sdcard/libnge2/demo10/" path)
#else
#define RES_PATH(path) (path)
#endif

//�˳���ʶ
int game_quit = 0;
//����ͼƬ
image_p p_bg = NULL;
//logoͼƬ
image_p p_logo  = NULL;
//logoͼƬ��ͼƬ����
int logomask1,logomask2;

#ifdef NGE_INPUT_BUTTON_SUPPORT
void btn_down(int keycode)
{
	switch(keycode)
    {
	case PSP_BUTTON_UP:
		break;
	case PSP_BUTTON_DOWN:
		break;
	case PSP_BUTTON_LEFT:
		break;
	case PSP_BUTTON_RIGHT:
		break;
	case PSP_BUTTON_TRIANGLE:
		break;
	case PSP_BUTTON_CIRCLE:
		break;
	case PSP_BUTTON_CROSS:
		break;
    case PSP_BUTTON_SQUARE:
		break;
	case PSP_BUTTON_SELECT:
		//����ѡ����˳�
		game_quit = 1;
		break;
	case PSP_BUTTON_START:
		//���¿�ʼ���˳�
		game_quit = 1;
		break;
    }
}
#endif

void DrawScene()
{
	BeginScene(1);
	ImageToScreen(p_bg,0,0);
	DrawImage(p_logo,0,0,0,0,128,0,256,256);
	DrawImageMask(p_logo,0,0,0,0,0/*dx*/,0/*dy*/,128/*dw*/,128/*dh*/,logomask1);
	DrawImageMask(p_logo,0,0,0,0,480-128/*dx*/,272-128/*dy*/,128/*dw*/,128/*dh*/,0x7fffffff);
	DrawImageMask(p_logo,0,0,0,0,0/*dx*/,272-128/*dy*/,128/*dw*/,128/*dh*/,logomask2);
	DrawImageMask(p_logo,0,0,0,0,480-128/*dx*/,0/*dy*/,128/*dw*/,128/*dh*/,logomask2);
	EndScene();
}

int init() {
	//��ʼ��NGE��ΪVIDEO,AUDIO��������ֻ��ʼ��VIDEO�������ʼ��������INIT_VIDEO|INIT_AUDIO,����INIT_ALL
	NGE_Init(INIT_VIDEO);
	//��ʼ����������btn_down�ǰ�����Ӧ,�����ǵ���ʱ����Ӧ��0����nge����home��Ϣ(ֱ���˳�),��1������PSPϵͳ����
	//home��Ϣ,ͨ����1�����˳���1.50������Ƴ�����Ҫ��0��
#ifdef NGE_INPUT_BUTTON_SUPPORT
	InitInput(btn_down,NULL,1);
#endif
	//���һ��������psp swizzle�Ż���ͨ����1
	p_bg = image_load(RES_PATH("images/demo0.jpg"),DISPLAY_PIXEL_FORMAT_8888,1);
	if(p_bg == NULL) {
		nge_print("can not open file\n");
	}
	p_logo = image_load(RES_PATH("images/nge2logo.png"),DISPLAY_PIXEL_FORMAT_4444,1);
	if(p_logo == NULL) {
		nge_print("can not open file\n");
	}
	//����һ����͸����ͼƬ����color
	logomask1 = CreateColor(255,255,255,128,p_logo->dtype);
	//��㴴��һ��ͼƬ����color
	logomask2 = CreateColor(100,100,100,255,p_logo->dtype);
	return 0;
}

int mainloop() {
	if (game_quit)
		return NGE_APP_QUIT;

	ShowFps();
#ifdef NGE_INPUT_HAS_PROC
	InputProc();
#endif
	DrawScene();

	return NGE_APP_NORMAL;
}

int fini() {
	image_free(p_bg);
	p_bg = NULL;
	image_free(p_logo);
	p_logo = NULL;
	NGE_Quit();
	return 0;
}

class MyApp : public CNgeApp
{
public:
	MyApp() : CNgeApp() {}
	~MyApp() {}

	virtual int Init() {
		return init();
	}
	virtual int Mainloop() {
		return mainloop();
	}
	virtual int Fini() {
		return fini();
	}
};

MyApp app;

extern "C"
int main(int argc, char* argv[])
{
	nge_registerApp(&app);
	return 0;
}
