/*=============================================================================

  Plugin: org.commontk.xnat

  Copyright (c) University College London,
    Centre for Medical Image Computing

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#include "ctkXnatConnectionTest.h"

#include <ctkXnatProject.h>
#include <ctkXnatServer.h>

// Qt includes
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QSignalSpy>
#include <QStringList>
#include <QTest>
#include <QTime>
#include <QTimer>
#include <QUrl>
#include <QUuid>

// --------------------------------------------------------------------------
void ctkXnatConnectionTestCase::initTestCase()
{
  QString serverUrl("https://central.xnat.org");
  QString userName("ctk");
  QString password("ctk");

  this->connection = new ctkXnatConnection();
  this->connection->setUrl(serverUrl);
  this->connection->setUserName(userName);
  this->connection->setPassword(password);
}

void ctkXnatConnectionTestCase::cleanupTestCase()
{
  delete this->connection;
}

void ctkXnatConnectionTestCase::testProjectList()
{
  bool success = false;

  ctkXnatServer* server = this->connection->server();
  this->connection->fetch(server);

  QList<ctkXnatObject*> projects = server->getChildren();
  int projectNumber = projects.size();

  QVERIFY(projectNumber > 0);
}

void ctkXnatConnectionTestCase::testCreateProject()
{
  // Create a random project name
  QUuid id = QUuid::createUuid();
  QString testProjectName = QString("CTK_TEST_%1").arg(id.toString().mid(1, 8));
  qDebug() << "test project name:" << testProjectName;

  ctkXnatServer* server = this->connection->server();

  // Check if there is NO project with that name
  this->connection->fetch(server);
  QList<ctkXnatObject*> projects = server->getChildren();
  bool found = false;
  int projectNumber = projects.size();
  foreach (ctkXnatObject* oProject, projects) {
    ctkXnatProject* project = qobject_cast<ctkXnatProject*>(oProject);
    if (project->name() == testProjectName) {
      found = true;
      break;
    }
  }
  QVERIFY(!found);

  // Create a project with that name
  ctkXnatProject* project = new ctkXnatProject(server);
  project->setName(testProjectName);
  project->setDescription("Test project created by the unit test of the CTK XNAT plugin.");
  this->connection->create(project);

  // Check if there IS a project with that name
  this->connection->fetch(server);
  projects = server->getChildren();
  found = false;
  projectNumber = projects.size();
  foreach (ctkXnatObject* oProject, projects) {
    ctkXnatProject* project = qobject_cast<ctkXnatProject*>(oProject);
    if (project->name() == testProjectName) {
      found = true;
      break;
    }
  }
  QVERIFY(found);

  // Remove the project
  this->connection->remove(project);

  // Check if there is NO project with that name
  this->connection->fetch(server);
  projects = server->getChildren();
  found = false;
  projectNumber = projects.size();
  foreach (ctkXnatObject* oProject, projects) {
    ctkXnatProject* project = qobject_cast<ctkXnatProject*>(oProject);
    if (project->name() == testProjectName) {
      found = true;
      break;
    }
  }

  // TODO The project is removed from the server, but not from the object
//  QVERIFY(!found);
}

// --------------------------------------------------------------------------
int ctkXnatConnectionTest(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);
  ctkXnatConnectionTestCase testCase;
  return QTest::qExec(&testCase, argc, argv);
}
