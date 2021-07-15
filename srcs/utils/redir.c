#include "minishell.h"

void process_redirects(t_main *main)
{
    if (main->job->pipe->redir->redir_type == OUTPUT)
        redir_one_right(main);
    if (main->job->pipe->redir->redir_type == APPEND_OUTPUT)
        redir_two_right(main);
    if (main->job->pipe->redir->redir_type == INPUT)
        redir_one_left(main);
    if (main->job->pipe->redir->redir_type == INPUT_MULTILINE)
        redir_two_left(main);
}
