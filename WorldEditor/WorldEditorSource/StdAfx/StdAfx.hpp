/*
 * StdAfx.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include <json/json.h>

#include <iostream>
#include <map>

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QTreeView>
#include <QtGui/QFileSystemModel>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QPaintEvent>

#include "MathLib/MathConstants.hpp"
#include "MathLib/ColorF.hpp"
#include "MathLib/GLBoxF.hpp"
#include "MathLib/Point.hpp"
#include "MathLib/PointF.hpp"
#include "MathLib/Box.hpp"
#include "MathLib/BoxF.hpp"
#include "MathLib/Size.hpp"
#include "MathLib/SizeF.hpp"
#include "MathLib/Colors.hpp"
#include "CommonUtils.hpp"
#include "WorldStructureAliases.hpp"
#include "CommonAliases.hpp"
#include "WorldStructureConstants.hpp"