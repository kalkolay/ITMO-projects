#include <iostream>

#include "backup_system/entities/Backup.h"

using namespace backup::entities;

int main()
{
    std::cout << "\n//______________________________Use-case №1______________________________//\n" << std::endl;

    FileInfo file1_1("1_1.txt");
    FileInfo file1_2("1_2.txt");
    Files files = { file1_1, file1_2 };
    std::cout << "Files added:\n";
    for (const auto& file : files)
    {
        std::cout << "\tFile: " << file.GetFile() << std::endl;
        std::cout << "\tName: " << file.GetName() << std::endl;
        std::cout << "\tExtension: " << file.GetExtension() << std::endl;
        std::cout << "\tParent path: " << file.GetParentPath() << std::endl;
        std::cout << "\tSize: " << file.GetSize() << " bytes" << std::endl;
        std::cout << "\tLast write time: " << file.GetLastWriteTime() << " GMT\n" << std::endl;
    }

    Backup backup(files);
    std::cout << "Backup initialized:\n";
    std::cout << "\tID: " << backup.GetId() << std::endl;
    std::cout << "\tCreation time: " << backup.GetCreationTime() << std::endl;
    std::cout << "\tSize: " << backup.GetSize() << " bytes\n" << std::endl;

    backup.CreateAbsoluteRestorePoint(Separate);
    std::cout << "Absolute restore point created. Backup files:\n";
    for ( const auto& p: fs::directory_iterator("backup_separate") )
        std::cout << '\t' << p.path() << std::endl;
    std::cout << std::endl;

    backup.CreateAbsoluteRestorePoint(Separate);
    std::cout << "Another absolute restore point created" << std::endl;
    std::cout << "Number of restore points: " << backup.GetRestorePoints().size() << std::endl;

    backup.CleanRestorePointsByNumber(1);
    std::cout << "Did restore points clean properly? "     << std::boolalpha
              << (backup.GetRestorePoints().size() == 1) << std::endl;

    std::cout << "\n//______________________________Use-case №2______________________________//\n" << std::endl;

    FileInfo file2_1("2_1.txt");
    FileInfo file2_2("2_2.txt");
    std::cout << "Files added:\n";
    std::cout << "\tSize of " << file2_1.GetFile() << " is " << file2_1.GetSize() << " bytes" << std::endl;
    std::cout << "\tSize of " << file2_2.GetFile() << " is " << file2_2.GetSize() << " bytes" << std::endl;
    std::cout << std::endl;

    Backup backup2;
    backup2.AddFile(file2_1);
    backup2.CreateAbsoluteRestorePoint(Separate);
    backup2.AddFile(file2_2);
    backup2.CreateAbsoluteRestorePoint(Separate);
    std::cout << "Backup initialized:\n";
    std::cout << "\tID: " << backup2.GetId() << std::endl;
    std::cout << "\tCreation time: " << backup2.GetCreationTime() << std::endl;
    std::cout << "\tSize: " << backup2.GetSize() << " bytes" << std::endl;
    std::cout << "\tNumber of restore points: " << backup2.GetRestorePoints().size() << std::endl << std::endl;

    backup2.CleanRestorePointsBySize(150);
    std::cout << "Did restore points clean properly? "      << std::boolalpha
              << (backup2.GetRestorePoints().size() == 1) << std::endl;

    std::cout << "\n//______________________________Use-case №3______________________________//\n" << std::endl;

    Backup backup3;
    backup3.AddFile(file1_1);
    backup3.CreateIncrementalRestorePoint(nullptr, Common);
    backup3.AddFile(file1_2);
    IncrementalRestorePoint point = std::get<IncrementalRestorePoint>( backup3.GetRestorePoints().front() );
    backup3.CreateIncrementalRestorePoint(&point, Common);

    std::cout << "\n//______________________________Use-case №4______________________________//\n" << std::endl;

    Backup backup4(files);
    backup4.CreateAbsoluteRestorePoint(Separate);
    backup4.AddFile(file2_1);
    backup4.CreateAbsoluteRestorePoint(Separate);
    std::cout << "\tNumber of restore points: " << backup4.GetRestorePoints().size() << std::endl;

    backup4.CleanRestorePointsHybrid(true,
                                     Number, 2,
                                     Size,   50);
    std::cout << "\tNumber of restore points: " << backup4.GetRestorePoints().size() << std::endl;
    backup4.CleanRestorePointsHybrid(false,
                                     Date,   "Friday, 20 November 2020 02:28",
                                     Number, 2,
                                     Size,   50);
    std::cout << "\tNumber of restore points: " << backup4.GetRestorePoints().size() << std::endl;

    return 0;
}
