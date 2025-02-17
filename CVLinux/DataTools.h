class DataTools{
	private:
		int		     fd=0;
		char* 		data=0x00;
		struct stat      filestat;

	public:
		int TouchFile(const char* path){
			fd=open(path, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
			if (fd < 0)
				return 1;
			close(fd);
			return 0;
		}
		char* ReadFile(const char* path){
			if (data)
				free(data);
			fd=open(path, O_RDONLY);
			if (fd < 0)
				return NULL;
			fstat(fd, &filestat);
			data=(char*)malloc(filestat.st_size);
			read(fd, data, filestat.st_size);
			close(fd);
			return data;
		}
		int  WriteFile(const char* path, const char* data){
			fd=open(path, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
			if (fd < 0)
				return 1;
			write(fd, data, strlen(data));
			close(fd);
			return 0;
		}
		int CorruptFile(const char* path, size_t size=0){
			fd=open(path, O_WRONLY);
			if (fd < 0)
				return 1;
			fstat(fd, &filestat);
			if (size != 0x00 && size < filestat.st_size)
				filestat.st_size=size;

			srand(time(0));

			for (int tmp=0; tmp<=filestat.st_size; tmp++){
				char byte=(char)( rand() % 255 );
				write(fd, &byte, 1);
			}
			close(fd);
			return 0;
		}

		int MoveFile(const char* Old, const char* New){
			if (rename(Old, New))
				return 1;
			return 0;
		}
		int DeleteFile(const char* path){
			if (remove(path))
				return 1;
			return 0;
		}
		~DataTools(){
			if (data!=0x00)
				free(data);
		}
};
