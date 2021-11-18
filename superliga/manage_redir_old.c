void	manage_redir(t_list **list, t_comm *comm, t_split *split)
{
	char	*str;
	char	*aux;

	comm->redir.fdin = 0;
	comm->redir.fdout = 0;
	//test_list(*list, comm);
	fprintf(stderr, "list next: %p\n", ((*list)->next));
	if (((t_comm*)(*list)->content)->prev_pipe)
		split->p_page++;
	fprintf(stderr, "word: %s page %d p_page: %d\n", ((t_comm*)(*list)->content)->t_word, ((t_comm*)(*list)->content)->page, split->p_page);
	str = NULL;
	//fprintf(stderr, "page: %d\n", split->p_page);
	//fprintf(stderr, "list: %p\n", list);
	while ((((t_comm *)((*list)->content))->page) == split->p_page)
	{
		fprintf(stderr, "en el page %d\n", split->p_page);
		//test_list(*list, comm);
		//fprintf(stderr, "PREPARSE %s\n", ((t_comm*)(*list)->content)->t_word);
		if (((t_comm *)((*list)->content))->t_word && !str)
			str = ft_strdup(((t_comm *)((*list)->content))->t_word);
		else if (!((t_comm *)((*list)->content))->t_word && str)
		{
			aux = str;
			if (((t_comm *)((*list)->content))->redir.rest)
			{
				str = ft_strjoin(str, ((t_comm *)((*list)
								->content))->redir.rest);
				free (aux);
			}
			if (comm->redir.fdout)
				close(comm->redir.fdout);
			if (comm->redir.fdin)
				close(comm->redir.fdin);
			if (((t_comm *)((*list)->content))->t_gt)
				comm->redir.fdout = \
					open(((t_comm *)((*list)->content))->redir.file, O_RDWR
						| O_TRUNC | O_CREAT, 0700);
			if (((t_comm *)((*list)->content))->t_gtgt)
				comm->redir.fdout = \
					open(((t_comm *)((*list)->content))->redir.file, O_RDWR
						| O_APPEND | O_CREAT, 0700);
			if (comm->redir.fdout)
				comm->redir.real_fdout = dup(1);
			if (((t_comm *)((*list)->content))->t_lt)
				comm->redir.fdin = \
					open(((t_comm *)((*list)->content))->redir.file, O_RDONLY);
			if (comm->redir.fdin)
				comm->redir.real_fdin = dup(0);
		}
		if ((((*list)->next) && ((((t_comm *)((*list)->next)->content)->t_semi) == 1 || (((t_comm *)((*list))->content)->post_pipe))) || ((*list)->next) == NULL) //FIXME: reevaluar uso de pages
		{
			((t_comm *)((*list)->content))->t_command = ft_strdup(str);
			fprintf(stderr, "PARSEAMOS %s\n", ((t_comm*)(*list)->content)->t_command);
			if (str)
				free(str);
			if (comm->redir.fdout)
				dup2(comm->redir.fdout, 1);
			if (comm->redir.fdin)
				dup2(comm->redir.fdin, 0);
			fprintf(stderr, "te parseo el comando\n");
			parse_command(*list, comm, split);
			//test_list(list, &comm);
			if (comm->redir.fdout)
			{
				close(comm->redir.fdout);
				dup2(comm->redir.real_fdout, 1);
				close (comm->redir.real_fdout);
			}
			if (comm->redir.fdin)
			{
				close(comm->redir.fdin);
				dup2(comm->redir.real_fdin, 0);
				close(comm->redir.real_fdin);
			}
			split->p_page++;
			fprintf(stderr, "ahora page es %d\n", split->p_page);
			if (((*list)->next) && ((t_comm *)((*list)->content))->post_pipe == 0)
				list = &((*list)->next);  //FIXME: que no siga parseando todos los pipes, que entre de uno en uno
		}
		if (((*list)->next) || ((t_comm *)((*list)->content))->page == 0)
		{
			if (((t_comm *)((*list)->content))->page == 0)
				str = NULL;
			list = &((*list)->next);
		}
	}
}