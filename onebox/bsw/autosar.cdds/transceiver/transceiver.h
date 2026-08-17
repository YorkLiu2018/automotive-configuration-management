/**
 *******************************************************************************
 * @file      transceiver.h
 * @brief     通信收发器驱动模块接口声明
 * @version   1.0.0
 * @date      2026-08-17
 * @note      本文件为 Git 版本管理演示用的 C 代码模板，可按需填充。
 *
 * 修改记录:
 *   版本     日期         作者       说明
 *   1.0.0   2026-08-17   demo       初始版本
 *******************************************************************************
 */
#ifndef TRANSCEIVER_H
#define TRANSCEIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== 版本信息 ==================== */
#define TRANSCEIVER_VERSION_STRING   "1.0.0"

/* ==================== 宏定义 ==================== */
/* TODO: 在此添加模块相关宏定义（如波特率等） */

/* ==================== 类型定义 ==================== */
/* TODO: 在此添加模块相关类型定义（如收发器状态枚举等） */

/* ==================== 函数声明 ==================== */
/**
 * @brief  模块初始化，系统上电时调用一次
 * @retval 无
 */
void Transceiver_Init(void);

/**
 * @brief  模块周期处理函数，由调度器周期调用
 * @retval 无
 */
void Transceiver_MainFunction(void);

/**
 * @brief  获取模块版本号字符串
 * @retval 形如 "1.0.0" 的版本字符串
 */
const char *Transceiver_GetVersion(void);

#ifdef __cplusplus
}
#endif

#endif /* TRANSCEIVER_H */
