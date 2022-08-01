#include <iostream>
#include "argparser/argparser.hpp"

// https://stackoverflow.com/a/478960
std::string cmd(const char *cmd)
{
    char buffer[128];
    std::string result = "";
    auto *pipe = popen(cmd, "r");
    if (!pipe)
        throw std::runtime_error("popen() failed!");
    try
    {
        while (fgets(buffer, sizeof buffer, pipe) != NULL)
        {
            result += buffer;
        }
    }
    catch (...)
    {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

void clone_repo(const char *repo, bool https)
{
    std::string command;
    command.append("git clone ");
    if (https)
    {
        command.append("https://github.com/")
            .append(repo)
            .append(".git");
    }
    else
    {
        command.append("git@github.com:")
            .append(repo)
            .append(".git");
    }

    std::cout << command << "\n";

    std::cout << cmd(command.c_str()) << "\n";
}

int main(int argc, char **argv)
{
    argparse::ArgumentParser program("gh");
    program.add_argument("-hs")
        .default_value(false)
        .implicit_value(true)
        .help("Use https instead of ssh.");
    program.add_argument("-r")
        .required()
        .help("user/repo");

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    if (auto repo = program.present("-r"))
        clone_repo(repo.value().c_str(), program.get<bool>("-hs"));
}