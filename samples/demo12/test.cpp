#include "libnge2.h"
#include "nge_app.hpp"

#include "cAnimation.h"

#include <stdio.h>

/**
 * ���԰�������
 */

#ifdef ANDROID
#define RES_PATH(path) ("/sdcard/libnge2/demo12/" path)
#else
#define RES_PATH(path) (path)
#endif

//�˳���ʶ
int game_quit = 0;

//����ͼƬ
image_p p_bg = NULL;

CAnimation* ani;

int init()
{
	//��ʼ��NGE��ΪVIDEO,AUDIO��������ֻ��ʼ��VIDEO�������ʼ��������INIT_VIDEO|INIT_AUDIO,����INIT_ALL
	NGE_Init(INIT_VIDEO);

	//���һ��������psp swizzle�Ż���ͨ����1
	p_bg = image_load("images/demo4_bg.png",DISPLAY_PIXEL_FORMAT_8888,1);
	if(p_bg == NULL) {
		printf("can not open file!\n");
	}
	ani = new CAnimation("images/demo4_man.png");

	return 0;
}

int mainloop()
{
	if (game_quit)
		return NGE_APP_QUIT;

	ShowFps();
	ani->Input();
	ani->Update();
	//draw target
	BeginScene(1);
	ImageToScreen(p_bg,0,0);
	ani->Show();
	EndScene();
	LimitFps(60);

	return NGE_APP_NORMAL;
}

int fini() {
	image_free(p_bg);
	delete ani;
	NGE_Quit();

	return 0;
}

nge_app_t app;

extern "C"
int main(int argc, char* argv[])
{
	nge_init_app(&app);
	app.init = init;
	app.mainloop = mainloop;
	app.fini = fini;
	nge_register_app(&app);

	return 0;
}
