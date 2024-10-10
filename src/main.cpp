#include <iostream>
#include <openvdb/openvdb.h>
#include <openvdb/tools/ChangeBackground.h>


int main() {
    std::cout << "Hello, World!" << std::endl;
    openvdb::initialize();
    openvdb::io::File file("wdas_cloud_sixteenth.vdb");
    file.open();

    openvdb::GridBase::Ptr baseGrid;
    for (openvdb::io::File::NameIterator nameIter = file.beginName();
         nameIter != file.endName(); ++nameIter) {
        baseGrid = file.readGrid(nameIter.gridName());
        if (nameIter.gridName() == "density") {
            std::cout << "reading grid " << nameIter.gridName() << std::endl;
            baseGrid = file.readGrid(nameIter.gridName());
        } else {
            std::cout << "skipping grid " << nameIter.gridName() << std::endl;
        }
    }
    file.close();
    std::cout << "Grid Type " << baseGrid->type() << std::endl;
    return 0;
}
