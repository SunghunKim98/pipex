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

	int i = -1;
	while (arr[++i])
		printf("%d: %s\n", i, arr[i]);
}

void	fork_fail()
{
	perror("Fork fail");
	exit(1);
}

static void	execute_command(t_cmd cmd)
{
	int		i;

	i = -1;
	while (++i < 5)
		execve(cmd.cmd[i], cmd.argv, cmd.envp);
	perror(cmd.argv[0]);
}

static void child_re(int *pipe_stuff, int index)
{
	pid_t   pid;
	int     pipe_re[2];
	t_cmd	cmd;
	int		status;

	if (index == 2)
	{
		dup2(pipe_stuff[STDOUT_FILENO], STDOUT_FILENO) // pipe로 넘기고
		// execute(); -> pipe_re[]
	}
	else
	{
		pipe(pipe_re);
		pid = fork();
		if (pid > 0) // parent
		{
			waitpid(pid, &status, 0); // 자식 프로세스가 종료될 때까지 여기서 Block상태로 대기.
			if (WIFSIGNALED(status)) // 비정상 종료
				exit(1);
			dup2(pipe_re[STDIN_FILENO], STDIN_FILENO)	// pipe로 받아와서
			// execute
		}
		else if (pid == 0) // child
		{
			child_re(pipe_re); // 재귀타러 들어감.
		}
		else
			fork_fail();
	}

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

	}
	else if (pid == 0) // child
	{

		child_re(pipefd[1]);
	}
	else
		fork_fail();



	// pipe(pipefd);
	// pid = fork();

	// if (pid > 0) // parent
	// {
	// 	waitpid(pid, &status, 0); // 자식 프로세스가 종료될 때까지 여기서 Block상태로 대기.
	// 	if (WIFSIGNALED(status)) // 비정상 종료
	// 		exit(1);
	// 	perror("asd");
	// 	redirect_out(argv[4]); // 여기서 출력되는 것들은 파일에 쓰겠다는 것을 의미 -> stdout의 화살표 방향을 바꿈.
	// 	dup2(pipefd[STDIN_FILENO], STDIN_FILENO); // 자식 프로세스에서 보낸 것을 pipefd[0]을 통해 받아온다.
	// 	close(pipefd[1]);
	// 	cmd_init(argv[3], &cmd);
	// 	execute_command(cmd); // 명령어를 실행하면, pipedfd[0]에서 read한 것들을 argv[4]의 파일에 쓰게 된다.
	// }
	// else if (pid == 0) // child
	// {
	// 	perror("asd");
	// 	redirect_in(argv[1]); // 여기서 어떤 파일을 읽어옴.
	// 	close(pipefd[0]);
	// 	dup2(pipefd[STDOUT_FILENO], STDOUT_FILENO); // 그 여기서 출력되는 부분들은 pipefd[1]로 들어간다.
	// 	cmd_init(argv[2], &cmd);
	// 	execute_command(cmd); // 여기서 실행하면 어떤 출력의 결과가 생기고 그 출력의 결과들은 pipefd[1]을 타고 들어간다.
	// }
	// else
	// {
	// 	perror("Fork fail");
	// 	exit(1);
	// }








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
