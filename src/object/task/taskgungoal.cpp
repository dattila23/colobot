// * This file is part of the COLOBOT source code
// * Copyright (C) 2001-2008, Daniel ROUX & EPSITEC SA, www.epsitec.ch
// *
// * This program is free software: you can redistribute it and/or modify
// * it under the terms of the GNU General Public License as published by
// * the Free Software Foundation, either version 3 of the License, or
// * (at your option) any later version.
// *
// * This program is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// * GNU General Public License for more details.
// *
// * You should have received a copy of the GNU General Public License
// * along with this program. If not, see  http://www.gnu.org/licenses/.

// taskgungoal.cpp


#include <windows.h>
#include <stdio.h>
#include <d3d.h>

#include "common/struct.h"
#include "graphics/d3d/d3dengine.h"
#include "math/old/math3d.h"
#include "common/event.h"
#include "common/misc.h"
#include "common/iman.h"
#include "object/object.h"
#include "sound/sound.h"
#include "object/task/task.h"
#include "object/task/taskgungoal.h"




// Object's constructor.

CTaskGunGoal::CTaskGunGoal(CInstanceManager* iMan, CObject* object)
						  : CTask(iMan, object)
{
}

// Object's destructor.

CTaskGunGoal::~CTaskGunGoal()
{
}


// Management of an event.

bool CTaskGunGoal::EventProcess(const Event &event)
{
	float		dir;

	if ( m_engine->RetPause() )  return true;
	if ( event.event != EVENT_FRAME )  return true;

	m_progress += event.rTime*m_speed;

	if ( m_progress < 1.0f )
	{
		dir = m_initialDirV + (m_finalDirV-m_initialDirV)*m_progress;
	}
	else
	{
		dir = m_finalDirV;
	}
	m_object->SetGunGoalV(dir);

	if ( m_progress < 1.0f )
	{
		dir = m_initialDirH + (m_finalDirH-m_initialDirH)*m_progress;
	}
	else
	{
		dir = m_finalDirH;
	}
	m_object->SetGunGoalH(dir);

	return true;
}


// Assigns the goal was achieved.

Error CTaskGunGoal::Start(float dirV, float dirH)
{
	float	speedV, speedH;
	int		i;

	m_initialDirV = m_object->RetGunGoalV();
	m_object->SetGunGoalV(dirV);
	m_finalDirV = m_object->RetGunGoalV();  // possible direction
	m_object->SetGunGoalV(m_initialDirV);  // gives initial direction

	if ( m_finalDirV == m_initialDirV )
	{
		speedV = 100.0f;
	}
	else
	{
		speedV = 1.0f/(fabs(m_finalDirV-m_initialDirV)*1.0f);
	}

	m_initialDirH = m_object->RetGunGoalH();
	m_object->SetGunGoalH(dirH);
	m_finalDirH = m_object->RetGunGoalH();  // possible direction
	m_object->SetGunGoalH(m_initialDirH);  // gives initial direction

	if ( m_finalDirH == m_initialDirH )
	{
		speedH = 100.0f;
	}
	else
	{
		speedH = 1.0f/(fabs(m_finalDirH-m_initialDirH)*1.0f);
	}

	m_speed = Math::Min(speedV, speedH);

	if ( m_finalDirV != m_initialDirV ||
		 m_finalDirH != m_initialDirH )
	{
		i = m_sound->Play(SOUND_MANIP, m_object->RetPosition(0), 0.3f, 1.5f, true);
		m_sound->AddEnvelope(i, 0.3f, 1.5f, 1.0f/m_speed, SOPER_STOP);
	}

	m_progress = 0.0f;

	return ERR_OK;
}

// Indicates whether the action is finished.

Error CTaskGunGoal::IsEnded()
{
	if ( m_engine->RetPause() )  return ERR_CONTINUE;

	if ( m_initialDirV == m_finalDirV &&
		 m_initialDirH == m_finalDirH )  return ERR_STOP;
	if ( m_progress < 1.0f )  return ERR_CONTINUE;

	m_object->SetGunGoalV(m_finalDirV);
	m_object->SetGunGoalH(m_finalDirH);
	Abort();
	return ERR_STOP;
}

// Suddenly ends the current action.

bool CTaskGunGoal::Abort()
{
	return true;
}
