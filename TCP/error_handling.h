void fd_errorcheck(int fd,const char* error_message)
{
    if(fd < 0){
        std::cerr << error_message;
        exit(1);
    }
}