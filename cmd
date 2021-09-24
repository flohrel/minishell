src/lexer/lexer1.c:	lexer = &vars->lexer;
src/lexer/lexer1.c:	lexer = &vars->lexer;
src/lexer/lexer1.c:	lexer = &vars->lexer;
src/lexer/lexer1.c:	lexer = &vars->lexer;
src/lexer/lexer1.c:	lexer = &vars->lexer;
src/lexer/lexer0.c:	lexer = &vars->lexer;
src/lexer/lexer0.c:	lexer = &vars->lexer;
src/lexer/lexer_utils.c:	lexer = &vars->lexer;
Binary file src/input/.input.c.swp matches
src/input/input.c:	vars->lexer.buffer = lst_alloc(len + 1,
src/input/input.c:			sizeof(*(vars->lexer.buffer)), vars);
src/input/input.c:	ft_strlcpy(vars->lexer.buffer, line_read, len + 1);
src/input/input.c:	vars->lexer.buffer = lst_alloc(i + 1, sizeof(*buffer), vars);
src/input/input.c:	ft_strlcpy(vars->lexer.buffer, buffer, i + 1);
src/utils/exit.c:	free_ptr_lst(&vars->ptr_list);
src/utils/exit.c:	free_env(vars->env);
src/utils/exit.c:	free_env(vars->exp);
src/utils/exit.c:	free_env(vars->agn);
src/utils/init.c:	vars->lexer.tk_list = NULL;
src/utils/init.c:	vars->lexer.buffer = NULL;
src/utils/init.c:	vars->ptr_list = NULL;
src/utils/init.c:	vars->nb_pipes = 0;
src/utils/init.c:	vars->pipes = NULL;
src/utils/init.c:	minishlvl = get_env_value("MINISHLVL", vars->env);
src/utils/init.c:		set_env_value(vars->env, "MINISHLVL", new_value);
src/utils/init.c:		if ((add_to_exp(&vars->env, tmp) < 0)
src/utils/init.c:			|| (add_to_exp(&vars->exp, tmp) < 0))
src/utils/init.c:		vars->env = parse_env(envp);
src/utils/init.c:		vars->exp = parse_env(envp);
src/utils/init.c:		vars->env = NULL;
src/utils/init.c:		vars->exp = NULL;
src/utils/init.c:	vars->agn = NULL;
src/utils/shell_lvl.c:	if (vars->env)
src/utils/shell_lvl.c:		nb = (get_env_value("SHLVL", vars->env));
src/utils/shell_lvl.c:	vars->env = set_env_value(vars->env, "SHLVL", lvlstr);
src/utils/shell_lvl.c:	if (!vars->env)
src/utils/shell_lvl.c:	vars->exp = set_env_value(vars->exp, "SHLVL", lvlstr);
src/utils/shell_lvl.c:	if (!vars->exp)
src/utils/memory.c:	ptr = garbage_collector(nmemb, size, &vars->ptr_list);
src/utils/memory.c:	ft_lstadd_front(&(vars->ptr_list), new);
Binary file src/utils/.init.c.swp matches
Binary file src/exec/.exec1.c.swp matches
Binary file src/exec/.find_cmd.c.swp matches
Binary file src/exec/.redir0.c.swp matches
src/exec/find_cmd.c:	paths = ft_split(get_env_value("PATH", vars->env), ':');
src/exec/pipes.c:		while (i < vars->nb_pipes)
src/exec/pipes.c:			close(vars->pipes_fd[i++]);
src/exec/redir0.c:	str = vars->lexer.buffer;
Binary file src/exec/.pipes.c.swp matches
src/exec/exec1.c:	find_cmd(param, args, env_to_tab(vars->env, vars), vars);
src/exec/exec1.c:	vars->nb_pipes = 0;
src/exec/exec1.c:	vars->pipes_fd[(vars->nb_pipes)++] = io->pipe[FD_OUT];
src/exec/exec1.c:	vars->pipes_fd[(vars->nb_pipes)++] = io->pipe[FD_IN];
src/exec/exec1.c:	vars->io.std_out = dup(FD_OUT);
src/exec/exec1.c:	vars->io.std_in = dup(FD_IN);
src/parser/ast_build0.c:	vars->exec_tree = list(vars, parser);
src/parser/parser_utils0.c:	var = get_env_value(data, vars->env);
src/builtins/cd.c:	cdpath = get_env_value("CDPATH", vars->env);
src/builtins/cd.c:		*path = (get_env_value("HOME", vars->env));
src/builtins/cd.c:		*path = get_env_value("OLDPWD", vars->env);
src/builtins/cd.c:		&& getcwd(s, 255) && ft_strcmp(get_env_value("PWD", vars->env), s) == 0
src/builtins/cd.c:	vars->env = set_env_value(vars->env, "OLDPWD",
src/builtins/cd.c:			get_env_value("PWD", vars->env));
src/builtins/cd.c:	if (!vars->env)
src/builtins/cd.c:	vars->exp = set_env_value(vars->exp, "OLDPWD",
src/builtins/cd.c:			get_env_value("PWD", vars->exp));
src/builtins/cd.c:	if (!vars->exp)
src/builtins/cd.c:	vars->env = set_env_value(vars->env, "PWD", s);
src/builtins/cd.c:	if (!vars->env)
src/builtins/unset.c:		vars->env = unset_key(args[i], vars->env);
src/builtins/unset.c:		vars->exp = unset_key(args[i], vars->exp);
src/builtins/export_next.c:	value = get_env_value(str, vars->agn);
src/builtins/export_next.c:	if (add_to_exp(&vars->env, block) < 0
src/builtins/export_next.c:		|| add_to_exp(&vars->exp, block) < 0)
src/builtins/export_next.c:	if (add_to_exp(&vars->env, cpy) < 0
src/builtins/export_next.c:		|| add_to_exp(&vars->exp, cpy) < 0)
src/builtins/export_next.c:	if (add_to_exp(&vars->exp, result) < 0)
src/builtins/export.c:		if (add_to_exp(&vars->env, result) < 0
src/builtins/export.c:			|| add_to_exp(&vars->exp, result) < 0)
src/builtins/export.c:		print_sorted_env(vars->exp);
src/builtins/pwd.c:	env = vars->env;
src/builtins/optionhandle.c:		ft_lstadd_front(&vars->ptr_list, new);
src/builtins/print_env.c:	env_print(vars->env);
src/builtins/cd_next.c:	pwd = get_env_value("PWD", vars->env);
src/builtins/cd_next.c:	vars->env = set_env_value(vars->env, "PWD", path);
src/builtins/cd_next.c:	if (!vars->env)
src/builtins/assign.c:	stack = get_env_value(block->key, vars->exp);
src/builtins/assign.c:		stack = get_env_value(block->key, vars->agn);
src/builtins/assign.c:	if (get_env_value(block->key, vars->exp))
src/builtins/assign.c:		if (add_to_exp(&vars->exp, block) < 0)
src/builtins/assign.c:		if (add_to_exp(&vars->env, block) < 0)
src/builtins/assign.c:	if (!vars->agn)
src/builtins/assign.c:		vars->agn = blockcpy(block);
src/builtins/assign.c:		if (add_to_exp(&vars->agn, block) < 0)
src/builtins/assign.c:				if (add_to_exp(&vars->env, res) < 0)
src/builtins/assign.c:				if (add_to_exp(&vars->exp, res) < 0)
