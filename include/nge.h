/**
 * @file  nge.h
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/02/12 09:34:32
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#ifndef _NGE_H
#define _NGE_H

#include "nge_common.h"

#define INIT_VIDEO 1
#define INIT_AUDIO 2
#define INIT_ALL   INIT_VIDEO|INIT_AUDIO

#ifdef __cplusplus
extern "C"{
#endif

/**
 *NGE��ʼ������
 *@param[in] flags ��ʼ����־λ,INIT_VIDEO(��Ƶ),INIT_AUDIO(��Ƶ)����INIT_ALL
 *@return ��
 */
	NGE_API void NGE_Init(int flags);

/**
 *NGE�˳�����
 *@return ��
 */
	NGE_API void NGE_Quit();

/**
 *������Ļ����
 *@param[in] winname ��������
 *@param[in] screen_width ���ڿ�
 *@param[in] screen_height ���ڸ�
 *@param[in] screen_bpp ����bpp,ͨ����32
 *@param[in] screen_full �Ƿ�ȫ��0-����,1-ȫ��
 *@return ��
 */
	NGE_API void NGE_SetScreenContext(const char* winname,int screen_width,int screen_height,int screen_bpp,int screen_full);

/**
 *������Ϸ����ʱ��ԭʼ�ֱ���
 *@param[in] width ���
 *@param[in] height �߶�
 *@return ��
 */
	NGE_API void NGE_SetOriginalResolution(int width,int height);

/**
 *����Ƭͷ������ַ
 *@param[in] path ��ַ
 */
	NGE_API void NGE_SetOPMoviePath(const char* path);

#ifdef NGE_PSP
/**
 *ע��PSP���˳��ص�
 *@param[in] cb_id �ص���ʶ��
 */
	NGE_API void NGE_RegisterPSPExitCallback(int cb_id);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _NGE_H */
