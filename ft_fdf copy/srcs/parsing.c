# include "fdf.h"
# include "../Lib/get_next_line/get_next_line.h"
# include "../Lib/Libft/libft.h"

/*
void map_parssing(t_fdf *map, char *string)
{
    map->map_y = 4; // À changer pour la vraie taille
    map->map_x = 3;

    map->map_data = malloc(map->map_y * sizeof(int *));
    if (!map->map_data)
        exit(-1);

    for (int i = 0; i < map->map_y; i++)
    {
        map->map_data[i] = malloc(map->map_x * sizeof(int));
        if (!map->map_data[i])
        {
            for (int j = 0; j < i; j++)
                free(map->map_data[j]);
            free(map->map_data);
            exit(-1);
        }
    }

    // Remplissage temporaire
    int values[4][3] = {
        {100, 100, 100},
        {100, 100, 100},
        {100, 100, 100},
        {100, 100, 100}
    };

    for (int y = 0; y < map->map_y; y++)
        for (int x = 0; x < map->map_x; x++)
            map->map_data[y][x] = values[y][x];
    string = string;
    printf("Map loaded successfully!\n");
    for (int y = 0; y < map->map_y; y++)
   {
      for (int x = 0; x < map->map_x; x++)
         printf("%d ", map->map_data[y][x]);
      printf("\n");
   }
}*/
/*
void map_parsing(t_fdf	*map, char *string)
{
   int		fd;
   char	*line;
   int		i;

   i = 0;
   fd = open(string, O_RDONLY);
   if (fd < 0)
   {
      perror("Error opening file");
      exit(EXIT_FAILURE);
   }
   while (get_next_line(fd, &line) > 0)
   {
      map->map_x++;
      free(line);
   }
   close(fd);
   fd = open(string, O_RDONLY);
   while (get_next_line(fd, &line) > 0)
   {
      map->map_y = ft_wordcount(line, ' ');
      free(line);
   }
   close(fd);
}*/


// Function to free allocated memory in case of an error
void free_map_data(t_fdf *map)
{
    if (!map->map_data)
        return;

    for (int i = 0; i < map->map_y; i++)
        free(map->map_data[i]);

    free(map->map_data);
}

// Function to count the number of columns (map_x) in the first line
int count_columns(char *line)
{
    int count = 0;
    int in_number = 0;

    while (*line)
    {
        if (*line != ' ' && in_number == 0)
        {
            in_number = 1;
            count++;
        }
        else if (*line == ' ')
        {
            in_number = 0;
        }
        line++;
    }
    return count;
}

// Function to determine the size of the map before allocating memory
void get_map_size(t_fdf *map, char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char *line;
    map->map_y = 0;
    map->map_x = 0;

    while ((line = get_next_line(fd)))
    {
        if (map->map_y == 0)
            map->map_x = count_columns(line);
        map->map_y++;
        free(line);
    }
    close(fd);
}
int	ft_atoi(const char *nptr)
{
	int	i;
	int	value;
	int	sign;

	i = 0;
	value = 0;
	sign = 1;
	while (nptr[i] == ' ' || ('\t' <= nptr[i] && nptr[i] <= '\r'))
	{
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		value = value * 10 + (nptr[i] - 48);
		i++;
	}
	return (value * sign);
}

void free_split(char **split)
{
    int i = 0;

    if (!split)
        return;

    while (split[i])
    {
        free(split[i]);
        i++;
    }

    free(split);
}


// Function to parse the map file and store values in `map->map_data`
void map_parsing(t_fdf *map, char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    get_map_size(map, filename);

    // Initialize min and max values
    map->map_min_z = 0;
    map->map_max_z = 0;

    // Allocate memory for map_data
    map->map_data = malloc(sizeof(int *) * map->map_y);
    if (!map->map_data)
    {
        perror("Error allocating memory for map_data");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char *line;
    int y = 0;

    // Parse each line of the file
    while ((line = get_next_line(fd)))
    {
        // Split the line into values
        char **values = ft_split(line, ' ');
        if (!values)
        {
            perror("Error parsing line");
            free(line);
            free_map_data(map);
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Allocate memory for the current row
        map->map_data[y] = malloc(sizeof(int) * map->map_x);
        if (!map->map_data[y])
        {
            perror("Error allocating memory for map_data[y]");
            free_split(values);
            free(line);
            free_map_data(map);
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Parse each value in the row
        for (int x = 0; x < map->map_x; x++)
        {
            map->map_data[y][x] = ft_atoi(values[x]);

            // Update min and max values
            if (map->map_data[y][x] < map->map_min_z)
                map->map_min_z = map->map_data[y][x];
            if (map->map_data[y][x] > map->map_max_z)
                map->map_max_z = map->map_data[y][x];
        }

        // Free the split line and the line itself
        free_split(values);
        free(line);
        y++;
    }

    close(fd);
    /*
    for(int i = 0; i < map->map_y; i++)
    {
        for (int j = 0; j < map->map_x; j++)
            printf("%d ", map->map_data[i][j]);
        printf("\n");
    }*/
}
