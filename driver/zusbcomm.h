/*
 * Copyright (c) 2024 Yuichi Nakamura (@yunkya2)
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _ZUSBCOMM_H_
#define _ZUSBCOMM_H_

#include <stdint.h>

struct zusb_rmtdata {       // must be 8bytes (head.S)
    uint8_t zusb_ch;        // ZUSB channel No.
    uint8_t hds_changed;    // remote HDS media change flag
    uint8_t hds_ready;      // remote HDS media ready flag
    uint8_t rmtflag;        // bit 0:SCSI IOCS patch flag / bit 7:RTC adjust flag
    uint8_t hds_parts[4];   // # of partitions for each HDSs
};

extern struct zusb_rmtdata *com_rmtdata;
extern union remote_combuf *comp;

int com_connect(int protected);
void com_disconnect(void);
void com_cmdres(void *wbuf, size_t wsize, void *rbuf, size_t rsize);

#define com_cmdres_init(type, opcode) \
    struct cmd_ ## type *cmd = (struct cmd_ ## type *)comp; \
    struct res_ ## type *res = (struct res_ ## type *)comp; \
    cmd->command = opcode;
#define com_cmdres_exec() \
    com_cmdres(cmd, sizeof(*cmd), res, sizeof(*res))

#endif /* _ZUSBCOMM_H_ */
