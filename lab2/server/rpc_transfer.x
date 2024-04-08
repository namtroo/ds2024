struct filename {
    string filename_val<>;
};

struct data {
    string data_val<>;
    int data_len;
};

program FILE_TRANSFER_PROG {
    version FILE_TRANSFER_VER {
        int OPEN_RPC(filename) = 1;
        void CLOSE_RPC(int) = 2;
        data READ_RPC(int) = 3;
    } = 1;
} = 0x31230000;

