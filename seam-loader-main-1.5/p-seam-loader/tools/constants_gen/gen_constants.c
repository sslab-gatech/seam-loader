#include "pseamldr_api_defs.h"
#include "../src/common/data_structures/pseamldr_data.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../include/pseamldr_basic_defs.h"
#include "../../include/pseamldr_basic_types.h"

int main(int argc, char* argv[])
{
    pseamldr_constants_t constants = {0};

    if (argc < 1)
    {
        printf("USAGE: ./<tool Name> <output_file> <size> <rip_offset>\n");
        return 1;
    }

    char* output_file = argv[1];

    uint32_t size = (uint32_t)atoi(argv[2]);

    if ((size % _4KB) != 0)
    {
        printf("Error - binary size is not 4 KB aligned - 0x%llx\n", size);
        return 7;
    }

    uint32_t rip_offset = (uint32_t)strtol(argv[3],NULL,16);

    constants.data_stack_size = 3 * _4KB;
    constants.code_region_size = size;
    constants.data_region_size = ROUND_UP(sizeof(pseamldr_data_t), _4KB);
    constants.keyhole_region_size = MAX_KEYHOLE_PER_LP * _4KB;
    constants.keyhole_edit_region_size = ROUND_UP(MAX_KEYHOLE_PER_LP * 8, _4KB);
    constants.entry_point_offset = rip_offset;

    printf("Generated constants:\n");
    printf("Data stack size = 0x%llx\n", constants.data_stack_size);
    printf("Code region size = 0x%llx\n", constants.code_region_size);
    printf("Data region size = 0x%llx (sizeof pseamldr_data = 0x%llx)\n", constants.data_region_size, sizeof(pseamldr_data_t));
    printf("Keyhole region size = 0x%llx\n", constants.keyhole_region_size);
    printf("Keyhole edit region size = 0x%llx\n", constants.keyhole_edit_region_size);
    printf("Entry point offset = 0x%llx\n", constants.entry_point_offset);

    FILE *fptr;

    fptr = fopen(output_file,"wb");
    if (fptr == NULL)
    {
        printf("Error: failed opening file %s\n", output_file);
        return 3;
    }
    size_t written = fwrite(&constants, sizeof(constants),1,fptr);
    fclose(fptr);

    if (written != 1)
    {
        printf("Error: struct wasn't successfully written to file\n");
        return 5;
    }

    return 0;
}


