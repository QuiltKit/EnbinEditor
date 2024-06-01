#include "enbin.h"


static u32 swapEndianness32(u32 value) {
    return ((value >> 24) & 0x000000FF) |
        ((value >> 8) & 0x0000FF00) |
        ((value << 8) & 0x00FF0000) |
        ((value << 24) & 0xFF000000);
}

static float swapEndiannessF32(float value) {
    u32 intval;
    std::memcpy(&intval, &value, sizeof(float));

    intval = swapEndianness32(intval);

    float result;
    std::memcpy(&result, &intval, sizeof(float));

    return result;
}

void EnbinEditor::printEnbinData(std::string input) {
    if (input.empty()) {
        printf("Error - input is empty\n");
        return;
    }

    Mapdata::Enbin::Header header;
    std::fstream file(input, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        printf("Error - failed to open file %s\n", input.c_str());
        return;
    }

    file.read((char*)&header, sizeof(Mapdata::Enbin::Header));
    printf("\n- Header Information - \n");
    printf("Value 0x4: 0x%X\n", swapEndianness32(header._4));
    printf("Value 0x8: 0x%X\n", swapEndianness32(header._8));
    printf("Value 0xC: 0x%X\n", swapEndianness32(header._C));
    printf("Filesize: %d bytes (excluding magic)\n", swapEndianness32(header.filesize));
    printf("Number of entries: %d\n\n", swapEndianness32(header.numEntries));


    for (int i = 0; i < swapEndianness32(header.numEntries); i++) {
        Mapdata::Enbin::EnemyEntry entry;
        file.read((char*)&entry, sizeof(Mapdata::Enbin::EnemyEntry));


        printf("- Entry %d Information -\n", i);
        printf("Enemy name: %s\n", entry.name);
        printf("Enemy behaviour: %s\n", entry.behavior);
        printf("Value 0x40: %s\n", entry._40);
        printf("Bead type: %s\n", entry.beadType);
        printf("Bead colour: %s\n", entry.beadColor);
        printf("Enemy direction: %s\n", entry.direction);
        printf("Enemy orientation: %s\n", entry.orientation);
        printf("Position 1: X: %f, Y: %f, Z: %f\n", swapEndiannessF32(entry.position1.x), swapEndiannessF32(entry.position1.y), swapEndiannessF32(entry.position1.z));
        printf("Position 2: X: %f, Y: %f, Z: %f\n", swapEndiannessF32(entry.position2.x), swapEndiannessF32(entry.position2.y), swapEndiannessF32(entry.position2.z));
        printf("Position 3: X: %f, Y: %f, Z: %f\n", swapEndiannessF32(entry.position3.x), swapEndiannessF32(entry.position3.y), swapEndiannessF32(entry.position3.z));
        printf("\n");
    }

    printf("\n");
    file.close();
}