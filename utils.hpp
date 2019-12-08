#include <fstream>
#include <string>

void exit_error(const std::string& message);

std::fstream open_file(
    const std::string& filename,
    std::ios_base::openmode mode = std::ios_base::in);

