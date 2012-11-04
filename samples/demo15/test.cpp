#include "libnge2.h"
#include "nge_app.h"
#include "hgeparticle.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * ��������
 */

#define RES_PATH(path) (path)

//�˳���ʶ
int game_quit = 0;
//����ͼƬ

image_p p_par = NULL;
hgeParticleSystem*	mParticleSys;
sprite_p mParticle = NULL;

nge_timer* timer;
//last tick;
int mlast = 0;
//dt��Ϊ��λ
float dt = 0;

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
		break;
	case PSP_BUTTON_START:
		//���¿�ʼ���˳�
		game_quit = 1;
		break;
    }
}
#endif

void Update()
{
	//ע��,����������ϵͳupdate������.������Ҫ��1000
	float dt = (float)((timer->get_ticks(timer)-mlast)/1000.0);
	mlast = timer->get_ticks(timer);
	mParticleSys->Update(dt);
}

void DrawScene()
{
	BeginScene(1);
	mParticleSys->Render();
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
	p_par = image_load(RES_PATH("par/particles.png"),DISPLAY_PIXEL_FORMAT_8888,1);
	if(p_par == NULL) {
		nge_print("can not open file\n");
	}
	//����sprite��ͼ
	mParticle = (sprite_p)malloc(sizeof(sprite_t));
	memset(mParticle,0,sizeof(sprite_t));
	mParticle->sprite_image = p_par;
	mParticle->sprite_clip.left= 0.0f;
	mParticle->sprite_clip.top= 0.0f;
	mParticle->sprite_clip.right= 32.0f;
	mParticle->sprite_clip.bottom = 32.0f;
	mParticle->sprite_center.x = 16.0f;
	mParticle->sprite_center.y = 16.0f;

	mParticleSys = new hgeParticleSystem(RES_PATH("par/particle1.psi"), mParticle);
	mParticleSys->MoveTo(480.0f/2, 272.0f/2,0);
	mParticleSys->Fire();
	timer = nge_timer_create();
	timer->start(timer);

	return 0;
}

int mainloop() {
	if (game_quit)
		return NGE_APP_QUIT;

	ShowFps();
#ifdef NGE_INPUT_HAS_PROC
	InputProc();
#endif
	Update();
	DrawScene();
	LimitFps(60);

	return NGE_APP_NORMAL;
}

int fini() {
	image_free(p_par);
	p_par = NULL;
	SAFE_FREE(mParticle);
	mParticle = NULL;
	delete mParticleSys;
	mParticleSys = NULL;
	nge_timer_free(timer);
	NGE_Quit();
	return 0;
}

static nge_app_t app;

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
