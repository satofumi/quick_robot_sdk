/*!
  \file
  \brief 走行コマンドの処理

  \author Satofumi KAMIMURA

  $Id: run_commands.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "run_commands.h"
#include "htoi.h"
#include "itoh.h"
#include "wheel_velocity.h"
#include "connection.h"
#include "odometry_calculate.h"
#include "update_parameter_id.h"
#include "imask.h"
#include "interrupt_priority.h"


static void set_current_velocity(run_t *run)
{
    run->path.translational_control.current_velocity =
        run->odometry.translational_velocity << VELOCITY_INTERNAL_SHIFT_WIDTH;
    run->path.rotational_control.current_velocity =
        run->odometry.rotational_velocity << VELOCITY_INTERNAL_SHIFT_WIDTH;
}


void handle_OP_command(const run_t *run)
{
    enum {
        DATA_FIRST = 4,
    };
    char response[] = "OP0\nxxxxxxxxyyyyyyyydddd\n";
    char *p = &response[DATA_FIRST];
    const odometry_t *odometry = &run->odometry;
    int i;

    // 応答を返す
    for (i = 0; i < NUMBER_OF_AXIS; ++i) {
        long mm = odometry_current_mm(odometry, i);
        itoh(p, mm, 4);
        p += 8;
    }
    itoh(p, run->odometry.direction, 2);

    connection_write(response, 25);
}


void handle_SA_command(run_t *run)
{
    unsigned char current_interrupt_priority = get_imask_exr();
    set_imask_exr(INTERRUPT_PRIORITY_ALL_MASK);

    // モードを変更し、目標速度を設定する
    run->path.is_controlling = 1;
    run->path.translational_control.target_velocity =
        run->path.default_translational_velocity;
    run->path.rotational_control.target_velocity =
        run->path.default_rotational_velocity;

    // 現在速度を設定する
    set_current_velocity(run);

    set_imask_exr(current_interrupt_priority);
}


void handle_ST_command(run_t *run)
{
    unsigned char current_interrupt_priority = get_imask_exr();
    set_imask_exr(INTERRUPT_PRIORITY_ALL_MASK);

    // モードを変更し、目標速度をゼロに設定する
    run->path.is_controlling = 0;
    run->path.translational_control.target_velocity = 0;
    run->path.rotational_control.target_velocity = 0;

    // 現在速度を設定する
    set_current_velocity(run);

    set_imask_exr(current_interrupt_priority);
}


void handle_SP_command(run_t *run, const char *line_buffer)
{
    (void)run;
    (void)line_buffer;
    // !!!

    // ID の読み出し
    // !!!

    // 設定の更新
    // !!!
}


void handle_WV_command(run_t *run, const char *line_buffer)
{
    int id;
    short velocity;
    char response[] = "WV0\n";
    unsigned char current_interrupt_priority = get_imask_exr();

    // パラメータの読み出し
    id = htoi(&line_buffer[2], 1);
    velocity = htoi(&line_buffer[3], 4);

    // !!! パースに失敗したら、エラー応答を返すようにするべき

    if ((id == 0) || (id == 1)) {
        set_imask_exr(INTERRUPT_PRIORITY_ALL_MASK);
        wheel_set_velocity(&run->wheel[id], velocity);
        run->run_system.mode = DIRECT_WHEEL_CONTROL;
        set_imask_exr(current_interrupt_priority);
    } else {
        // ID 範囲外のエラー
        response[2] = '2';
    }

    connection_write(response, 4);
}
