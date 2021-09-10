	while (list)
	{
		i = 0;
		j = 0;
		if (((t_comm*)list->content)->t_word)
		{
			splitlt = ft_splitshell(split, ((t_comm*)list->content)->t_word, '<');
			while (splitlt[i])
				i++;
			h = 0;
			if (i > 1)
			{
				while (j < i * 2 - 1 && list)
				{
					if (j == 0)
					{
						free(((t_comm*)list->content)->t_word);
						((t_comm*)list->content)->t_word = NULL;
						((t_comm*)list->content)->t_word = ft_strdup(splitlt[h]);
						h++;
					}
					else
					{
						new = malloc(sizeof(t_list));   //TODO: mirar ahorrar lineas list_new
						otro = malloc(sizeof(t_comm));
						new->content = otro;
						ft_init(otro);
						if (j % 2 == 0 && j != 0)
						{
							((t_comm*)new->content)->t_word = ft_strdup(splitlt[h]);
							h++;
						}
						else if (j % 2 != 0)
							((t_comm*)new->content)->t_lt = 1;
						ft_lstadd_middle(&list, &new);
						list = list->next;
					}
					j++;
				}
			}
			else
			{
				free(splitlt[0]);
				splitlt[0] = NULL;
			}
			ft_malloc_free(comm, splitlt);
		}
		else
			free(((t_comm*)list->content)->t_word);
		list = list->next;
	}