/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/****************************************************************************
**
** This file is part of a Qt Solutions component.
** 
** Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
** 
** Contact:  Qt Software Information (qt-info@nokia.com)
** 
** Commercial Usage  
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Solutions Commercial License Agreement provided
** with the Software or, alternatively, in accordance with the terms
** contained in a written agreement between you and Nokia.
** 
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
** 
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
** 
** GNU General Public License Usage 
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
** 
** Please note Third Party Software included with Qt Solutions may impose
** additional restrictions and it is the user's responsibility to ensure
** that they have met the licensing requirements of the GPL, LGPL, or Qt
** Solutions Commercial license and the relevant license of the Third
** Party Software they are using.
** 
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** 
****************************************************************************/

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "qtlockedfile.h"

bool QtLockedFile::lock(LockMode mode, bool block)
{
    if (!isOpen()) {
        qWarning("QtLockedFile::lock(): file is not opened");
        return false;
    }
 
    if (mode == NoLock)
        return unlock();
           
    if (mode == m_lock_mode)
        return true;

    if (m_lock_mode != NoLock)
        unlock();

    struct flock fl;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fl.l_type = (mode == ReadLock) ? F_RDLCK : F_WRLCK;
    int cmd = block ? F_SETLKW : F_SETLK;
    int ret = fcntl(handle(), cmd, &fl);
    
    if (ret == -1) {
        if (errno != EINTR && errno != EAGAIN)
            qWarning("QtLockedFile::lock(): fcntl: %s", strerror(errno));
        return false;
    }

    
    m_lock_mode = mode;
    return true;
}


bool QtLockedFile::unlock()
{
    if (!isOpen()) {
        qWarning("QtLockedFile::unlock(): file is not opened");
        return false;
    }

    if (!isLocked())
        return true;

    struct flock fl;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fl.l_type = F_UNLCK;
    int ret = fcntl(handle(), F_SETLKW, &fl);
    
    if (ret == -1) {
        qWarning("QtLockedFile::lock(): fcntl: %s", strerror(errno));
        return false;
    }
    
    m_lock_mode = NoLock;
    return true;
}

QtLockedFile::~QtLockedFile()
{
    if (isOpen())
        unlock();
}
