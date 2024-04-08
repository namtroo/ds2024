const BUFFER_SIZE = 1024;

struct file_chunk {
    int size;
    char data[BUFFER_SIZE];
};

program FILE_TRANSFER {
    version FILE_TRANSFER_VERSION {
        file_chunk send_file(string) = 1;
    } = 1;
} = 0x31234567;

