A Bigger Use-case
@pause
>> 2D Platformer
@pause
   NOTE: Just the animation state machine logic.

@pause
@open assets\\fabulous_demo.gif
---

@color yellow
#ifndef HERO_H
#define HERO_H

#include <cute_coroutine.h>

#define HERO_SPRITE_LAYER 2
@color normal

// This file just implements animation/rendering logic.
// The state machine is intended to be driven externally.

typedef enum hero_state_t
{
	HERO_STATE_IDLE,
	HERO_STATE_RUN,
	HERO_STATE_JUMP,
} hero_state_t;

typedef enum facing_t
{
	FACING_LEFT,
	FACING_RIGHT
} facing_t;

typedef struct hero_t
{
	hero_state_t state;
	facing_t facing;

	coroutine_t co;
	int image_id;
} hero_t;

void hero_set_state(hero_t* hero, hero_state_t state);
void hero_update(hero_t* hero, float dt);
void hero_draw(hero_t* hero, v2 pos);
void hero_init(hero_t* hero);
void hero_set_facing(hero_t* hero, facing_t facing);

enum hero_image_id_t
{
	HERO_IMAGE_ID_IDLE0 = 140,
	HERO_IMAGE_ID_IDLE1,
	HERO_IMAGE_ID_IDLE2,
	HERO_IMAGE_ID_IDLE3,

	HERO_IMAGE_ID_RUN0,
	HERO_IMAGE_ID_RUN1,
	HERO_IMAGE_ID_RUN2,
	HERO_IMAGE_ID_RUN3,
	HERO_IMAGE_ID_RUN4,
	HERO_IMAGE_ID_RUN5,
	HERO_IMAGE_ID_RUN6,
	HERO_IMAGE_ID_RUN7,

	HERO_IMAGE_ID_JUMP0,
	HERO_IMAGE_ID_JUMP1,
};

@color yellow
#endif // HERO_H

#ifdef HERO_IMPLEMENTATION
#ifndef HERO_IMPLEMENTATION_ONCE
#define HERO_IMPLEMENTATION_ONCE

#include <sprite.h>
@color normal

void hero_set_state(hero_t* hero, hero_state_t state)
{
	hero->state = state;
	coroutine_init(&hero->co);
}

void hero_set_facing(hero_t* hero, facing_t facing)
{
	hero->facing = facing;
}

void hero_state_idle(hero_t* hero, float dt)
{
	const float idle_time = 0.1f;
	const float idle_pause_time = 0.35f;
	coroutine_t* co = &hero->co;

	COROUTINE_START(co);
	COROUTINE_CASE(co, idle_start);

		hero->image_id = HERO_IMAGE_ID_IDLE0;
		COROUTINE_WAIT(co, idle_pause_time, dt);

		hero->image_id = HERO_IMAGE_ID_IDLE1;
		COROUTINE_WAIT(co, idle_time, dt);

		hero->image_id = HERO_IMAGE_ID_IDLE2;
		COROUTINE_WAIT(co, idle_time, dt);

		hero->image_id = HERO_IMAGE_ID_IDLE3;
		COROUTINE_WAIT(co, idle_pause_time, dt);

		hero->image_id = HERO_IMAGE_ID_IDLE2;
		COROUTINE_WAIT(co, idle_time, dt);

		hero->image_id = HERO_IMAGE_ID_IDLE1;
		COROUTINE_WAIT(co, idle_time, dt);

	goto idle_start;
	COROUTINE_END(co);
}

void hero_state_run(hero_t* hero, float dt)
{
	const float run_time = 0.1f;
	coroutine_t* co = &hero->co;

	COROUTINE_START(co);
	COROUTINE_CASE(co, run_start);

		hero->image_id = HERO_IMAGE_ID_RUN0;
		COROUTINE_WAIT(co, run_time, dt);

		hero->image_id = HERO_IMAGE_ID_RUN1;
		COROUTINE_WAIT(co, run_time, dt);

		hero->image_id = HERO_IMAGE_ID_RUN2;
		COROUTINE_WAIT(co, run_time, dt);

		hero->image_id = HERO_IMAGE_ID_RUN3;
		COROUTINE_WAIT(co, run_time, dt);

		hero->image_id = HERO_IMAGE_ID_RUN4;
		COROUTINE_WAIT(co, run_time, dt);

		hero->image_id = HERO_IMAGE_ID_RUN5;
		COROUTINE_WAIT(co, run_time, dt);

		hero->image_id = HERO_IMAGE_ID_RUN6;
		COROUTINE_WAIT(co, run_time, dt);

		hero->image_id = HERO_IMAGE_ID_RUN7;
		COROUTINE_WAIT(co, run_time, dt);

	goto run_start;
	COROUTINE_END(co);
}

void hero_state_jump(hero_t* hero, float dt)
{
	coroutine_t* co = &hero->co;

	COROUTINE_START(co);

		hero->image_id = HERO_IMAGE_ID_JUMP0;
		COROUTINE_WAIT(co, 0.15f, dt);

		hero->image_id = HERO_IMAGE_ID_JUMP1;
		COROUTINE_EXIT(co);

	COROUTINE_END(co);
}

void hero_update(hero_t* hero, float dt)
{
	switch (hero->state)
	{
	case HERO_STATE_IDLE:
		hero_state_idle(hero, dt);
		break;

	case HERO_STATE_RUN:
		hero_state_run(hero, dt);
		break;

	case HERO_STATE_JUMP:
		hero_state_jump(hero, dt);
		break;
	}
}

void hero_draw(hero_t* hero, v2 pos)
{
	sprite_t hero_sprite = make_sprite(hero->image_id, pos.x, pos.y, 1.0f, 0, HERO_SPRITE_LAYER);
	if (hero->facing == FACING_LEFT)
	{
		hero_sprite.sx *= -1.0f;
	}
	push_sprite(hero_sprite);
}

void hero_init(hero_t* hero)
{
	hero->state = HERO_STATE_IDLE;
	hero->facing = FACING_LEFT;
	coroutine_init(&hero->co);
	hero->image_id = ~0;
}

@color yellow
#endif // HERO_IMPLEMENTATION_ONCE
#endif // HERO_IMPLEMENTATION
@color normal
