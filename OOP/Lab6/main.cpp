#include "UIL/CollaboratorManager.h"
#include "UIL/TaskManager.h"
#include "UIL/ReportManager.h"

using namespace reports::ui;

int main()
{
    auto* collaboratorManager = new CollaboratorManager();
    collaboratorManager->AddCollaborator();
    collaboratorManager->AddCollaborator();
    collaboratorManager->AddCollaborator();
    collaboratorManager->SetSupervisor();

    auto* taskManager = new TaskManager();
    taskManager->AddTask();
    taskManager->AddTask();

    auto* reportManager = new ReportManager();
    reportManager->CreateDailyReport();
    reportManager->CreateSprintReport();
    reportManager->CreateCommandReport();

    return 0;
}