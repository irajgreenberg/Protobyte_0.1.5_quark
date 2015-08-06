#include "protocreator.h"
#include "ui_protocreator.h"

ProtoCreator::ProtoCreator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProtoCreator)
{
    ui->setupUi(this);
}

ProtoCreator::~ProtoCreator()
{
    delete ui;
}

void ProtoCreator::on_runButton_clicked()
{
    QString usrEntry = ui->inputText->toPlainText();

    QString projName = usrEntry.simplified();
    projName = projName.replace(" ", "_");
    //add check to ensure only alpanumeric characters are used?
    setSlnString(projName);
    runScript(projName);
}

void ProtoCreator::runScript(const QString& usrProjName){
    QString projectName = usrProjName;
    QString projectsDirName = "Projects";
    QString templateDirName = "ProtoTemplate";
    QString templateProjectName = "__Protobyte_Project_Template__";
    QString ext0 = ".vcxproj";
    QString ext1 = ".vcxproj.filters";
    QString extNames [2] = { ext0, ext1 };

    //Set up QFile Dialog - not sure if necessary
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::List);

    //Establish home directory path for checks to avoid infinite while loop
    QString homeDirPath = QDir::home().path();

    QDir currentDir = dialog.directory();

    bool projectsExists = currentDir.exists(projectsDirName);
    bool templateExists = currentDir.exists(templateDirName);

    //navigate from "Creator" Directory to "Protobyte" Directory
    while (!projectsExists && !templateExists){
        currentDir.cdUp();
        if (currentDir.path() == homeDirPath) {
            ui->outputText->appendPlainText("Cannot locate proper directories.");
            break;
        }
        projectsExists = currentDir.exists(projectsDirName);
        templateExists = currentDir.exists(templateDirName);
    }

    //Check to make sure that both Projects and Template folders Exist
    projectsExists = currentDir.exists(projectsDirName);
    templateExists = currentDir.exists(templateDirName);

    QString protobyteDirPath;

    if (projectsExists && templateExists) {
        protobyteDirPath = currentDir.path();

        currentDir.cd(projectsDirName);

        bool projectNameTaken = currentDir.exists(projectName);

        if(!projectNameTaken) {
            currentDir.mkdir(projectName);

            currentDir.cd(projectName);

            QString projectsPath;
            projectsPath = currentDir.path();

            //Navigate into Template Directory
            currentDir.cd(protobyteDirPath);
            currentDir.cd(templateDirName);
            currentDir.cd(templateProjectName);

            QString templatesPath;
            templatesPath = currentDir.path();

            //Copy files into new project directory
            QDirIterator iteration(currentDir, QDirIterator::Subdirectories);
            QString copyLocation;
            while (iteration.hasNext()) {
                iteration.next();
                copyLocation = projectsPath + "/" + iteration.fileName();
                QFile::copy(iteration.filePath(), copyLocation);
            }

            //navigate to proper projects folder
            currentDir.cd(projectsPath);

            //rename template files
            QString oldPath;
            QString newPath;
            for (int i = 0; i < 2; i++) {
                if(currentDir.exists(templateProjectName + extNames[i])) {
                    oldPath = currentDir.path() + "/" + templateProjectName + extNames[i];
                    newPath = currentDir.path() + "/" + projectName + extNames[i];
                    QFile::rename(oldPath, newPath);
                }
                else {
                    ui->outputText->appendPlainText("Error. Cannot find proper files. Project creation failed.");
                }
            }
            QString newFileName = projectName + ".sln";
            QString newFilePath = projectsPath + "/" + newFileName;

            QFile slnFile(newFilePath);
            if (slnFile.open(QIODevice::WriteOnly)) {
                QTextStream out(&slnFile);
                out << slnString;
            }
            slnFile.close();
            currentDir.cd(projectsPath);
            if (currentDir.exists(newFileName)) {
                ui->outputText->appendPlainText("Success! " + projectName + " has been created.");
            } else {
                ui->outputText->appendPlainText("Error. Visual Studios solution file not created. Project creation failed.");
            }
        } else {
            ui->outputText->appendPlainText("Project name already taken. Cannot complete project creation.");
        }
    } else {
       ui->outputText->appendPlainText("Cannot locate proper directories.");
    }

    //TO DO:
        //Create visual studios .sln file
        //What is global selection, and is that needed here?
        //Do I need to check which version of Visual Studios is on the machine?
        //How would I get this to open the folder containing the project or open the project
            //itself?
}

void ProtoCreator::print(const QString& myString) {
    std::cout << myString.toStdString() << std::endl;
}

void ProtoCreator::setSlnString(const QString& usrProjName) {
    QString newLine = "\r\n";
    slnString += "\"Microsoft Visual Studio Solution File, Format Version 12.00" + newLine;
    slnString += "# Visual Studio 2013" + newLine;
    slnString += "VisualStudioVersion = 12.0.21005.1" + newLine;
    slnString += "MinimumVisualStudioVersion = 10.0.40219.1" + newLine;
    slnString += "Project(\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\") = \"" + usrProjName + "\", \"" + usrProjName + ".vcxproj\", \"{4DF3E3D9-2197-48F1-80E4-3F0E3E408694}\"" + newLine;
    slnString += "EndProject" + newLine;
    slnString += "Global" + newLine;
    slnString += "GlobalSection(SolutionConfigurationPlatforms) = preSolution" + newLine;
    slnString += "Debug|Win32 = Debug|Win32" + newLine;
    slnString += "Release|Win32 = Release|Win32" + newLine;
    slnString += "EndGlobalSection" + newLine;
    slnString += "GlobalSection(ProjectConfigurationPlatforms) = postSolution" + newLine;
    slnString += "{4DF3E3D9-2197-48F1-80E4-3F0E3E408694}.Debug|Win32.ActiveCfg = Debug|Win32" + newLine;
    slnString += "{4DF3E3D9-2197-48F1-80E4-3F0E3E408694}.Debug|Win32.Build.0 = Debug|Win32" + newLine;
    slnString += "{4DF3E3D9-2197-48F1-80E4-3F0E3E408694}.Release|Win32.ActiveCfg = Release|Win32" + newLine;
    slnString += "{4DF3E3D9-2197-48F1-80E4-3F0E3E408694}.Release|Win32.Build.0 = Release|Win32" + newLine;
    slnString += "EndGlobalSection" + newLine;
    slnString += "GlobalSection(SolutionProperties) = preSolution" + newLine;
    slnString += "HideSolutionNode = FALSE" + newLine;
    slnString += "EndGlobalSection" + newLine;
    slnString += "EndGlobal\""  + newLine;
}
