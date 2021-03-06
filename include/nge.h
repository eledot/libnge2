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
 *NGE初始化函数
 *@param[in] flags 初始化标志位,INIT_VIDEO(视频),INIT_AUDIO(音频)或者INIT_ALL
 *@return 无
 */
	NGE_API void NGE_Init(int flags);

/**
 *NGE退出函数
 *@return 无
 */
	NGE_API void NGE_Quit();

/**
 *设置屏幕窗口
 *@param[in] winname 窗口名字
 *@param[in] screen_width 窗口宽
 *@param[in] screen_height 窗口高
 *@param[in] screen_bpp 窗口bpp,通常填32
 *@param[in] screen_full 是否全屏0-窗口,1-全屏
 *@return 无
 */
	NGE_API void NGE_SetScreenContext(const char* winname,int screen_width,int screen_height,int screen_bpp,int screen_full);

/**
 *设置游戏制作时的原始分辨率
 *@param[in] width 宽度
 *@param[in] height 高度
 *@return 无
 */
	NGE_API void NGE_SetOriginalResolution(int width,int height);

/**
 *设置片头动画地址
 *@param[in] path 地址
 */
	NGE_API void NGE_SetOPMoviePath(const char* path);

#ifdef NGE_PSP
/**
 *注册PSP的退出回调
 *@param[in] cb_id 回调标识号
 */
	NGE_API void NGE_RegisterPSPExitCallback(int cb_id);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _NGE_H */
