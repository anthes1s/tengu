#include "render-file-status.h"

RenderStatus::RenderStatus()
{
    qDebug() << "RenderStatus constructed!\n";
}

RenderStatus::RenderStatus(QStringList strlst)
{
    qDebug() << "RenderStatus constructed!\n";

    for(int i{0}; i < strlst.size(); ++i) {
        renderName.push_back(new QLabel(strlst[i]));
        renderStatus.push_back(new QLabel("Rendering..."));
    }
}

RenderStatus::~RenderStatus()
{
    for(QLabel* i : renderName) delete i;
    qDebug() << "renderNames destroyed!\n";
    for(QLabel* i : renderStatus) delete i;
    qDebug() << "renderStatuses destroyed!\n";
    qDebug() << "RenderStatus destroyed!\n";
}

QLabel* RenderStatus::getName(int i){
    return renderName[i];
}

QLabel* RenderStatus::getStatus(int i){
    return renderStatus[i];
}
