/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2014, Daniel Roux, EPSITEC SA & TerranovaTeam
 * http://epsiteс.ch; http://colobot.info; http://github.com/colobot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://gnu.org/licenses
 */

// gauge.h

#pragma once

#include "graphics/engine/engine.h"

#include "common/event.h"
#include "common/misc.h"

#include "ui/control.h"


namespace Ui {

class CGauge : public CControl
{
public:
    CGauge();
    virtual ~CGauge();

    bool    Create(Math::Point pos, Math::Point dim, int icon, EventType eventType);

    bool    EventProcess(const Event &event);

    void    Draw();

    void    SetLevel(float level);
    float   GetLevel();

protected:
    float   m_level;
};


}

