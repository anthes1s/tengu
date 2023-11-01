#include "render-file-status.h"

RenderStatus::RenderStatus(QStringList str_list)
{
    for(int i{0}; i < str_list.size(); ++i) {
        renderName.push_back(new QLabel(str_list[i]));
        renderStatus.push_back(new QLabel("Rendering..."));
    }
}

RenderStatus::~RenderStatus()
{
    for(QLabel* i : renderName) delete i;
    for(QLabel* i : renderStatus) delete i;
}

QLabel* RenderStatus::getName(int i){
    return renderName[i];
}

QLabel* RenderStatus::getStatus(int i){
    return renderStatus[i];
}
