/**
 * @file tx_command.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-26
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN

/**
 * @brief Record Command
 *
 */
PRO_DEF_MEM_DISPATCH(RecordCommandImpl, recordCommand);


/**
 * @brief Submit Command
 *
 */
PRO_DEF_MEM_DISPATCH(SubmitCommandImpl, submitCommand);


struct TXCommandProxy : pro::facade_builder ::build {};

TX_NAMESPACE_END
