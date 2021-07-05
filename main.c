#include "pipex.h"

int redirect_in(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int redirect_out(const char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static void	connect_pipe(int pipefd[2], int io)
{
	dup2(pipefd[io], io);
	close(pipefd[0]);
	close(pipefd[1]);
}

static void cmd_init(const char *cmd, t_cmd *p)
{
	char	**arr;

	arr = ft_split(cmd, ' ');
	p->cmd[0] = ft_strjoin("/bin/", arr[0]);
	p->cmd[1] = ft_strjoin("/sbin/", arr[0]);
	p->cmd[2] = ft_strjoin("/usr/local/bin/", arr[0]);
	p->cmd[3] = ft_strjoin("/usr/bin/", arr[0]);
	p->cmd[4] = ft_strjoin("/usr/sbin/", arr[0]);
	p->argv = (char *const *)arr;
	p->envp = 0;
}

static void	run_cmd(t_cmd cmd)
{
	int		i;

	i = -1;
	while (++i < 5)
		execve(cmd.cmd[i], cmd.argv, cmd.envp);
	perror(cmd.argv[0]);
}


int main(int argc, char **argv)
{
	pid_t   pid;
	int     pipefd[2];
	t_cmd	cmd;
	int		status;

	pipe(pipefd);
	pid = fork();
	if (pid > 0) // parent
	{
		// 신호를 주지 않아도 child에서 exit하니까 알아서 꺼지는데??
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			exit(1);

		redirect_out(argv[4]);
		connect_pipe(pipefd, STDIN_FILENO);
		cmd_init(argv[3], &cmd);
		run_cmd(cmd);
	}
	else if (pid == 0) // child
	{
		redirect_in(argv[1]);
		connect_pipe(pipefd, STDOUT_FILENO);
		cmd_init(argv[2], &cmd);
		run_cmd(cmd);
	}


	// pid_t	pid;

	// pid = fork();

	// if (pid > 0)
	// 	while (1)	printf("O");
	// else if (pid == 0)
	// 	while (1)	printf("X");
	// else
	// 	printf("Error");



	// redirect_in(argv[1]); // argv[1]이라는 파일을 STDIN으로 받아옴.
	// execve("/bin/cat", 0, 0); // STDIN으로 받아온 것을 실행.

	// redirect_out(argv[2]); // argv[2]라는 파일을 STDOUT으로 받아옴. 출력되는 것들은 argv[2]의 파일에 쓰인다.

	// printf("hihi here's out\n");
	// printf("hollly\n");


	return (0);
}