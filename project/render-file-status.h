#ifndef RENDERFILESTATUS_H
#define RENDERFILESTATUS_H

#include <QLabel>

class RenderStatus {
public:
    RenderStatus(QStringList);
    ~RenderStatus();
    QLabel* getName(int);
    QLabel* getStatus(int);
private:
    std::vector<QLabel*> renderName;
    std::vector<QLabel*> renderStatus;
};

#endif // RENDERFILESTATUS_H
