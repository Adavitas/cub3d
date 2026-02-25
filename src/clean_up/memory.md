Memory Management & Cleanup Guide for cub3d
1️⃣ Writing Safe Cleanup Functions
✅ Key Rule About free
free(NULL);   // Safe, does nothing


But:

free(ptr);
free(ptr);    // ❌ Undefined behavior (double free)

🔹 Golden Rule

After freeing memory, always set the pointer to NULL.

✅ Safe Free Pattern

Use a pointer-to-pointer:

void safe_free(void **ptr)
{
    if (!ptr || !*ptr)
        return;
    free(*ptr);
    *ptr = NULL;
}


Usage:

safe_free((void **)&game->map.grid);
safe_free((void **)&game->textures.north);


This prevents:

Double free

Freeing uninitialized memory

Dangling pointers

2️⃣ Freeing Nested Structures Properly

Example:

typedef struct s_map
{
    char    **grid;
    int     height;
} t_map;


Proper cleanup:

void free_map(t_map *map)
{
    int i;

    if (!map)
        return;

    if (map->grid)
    {
        i = 0;
        while (i < map->height)
        {
            free(map->grid[i]);
            i++;
        }
        free(map->grid);
        map->grid = NULL;
    }
}

Important

Do NOT free map itself here.

Only free what was dynamically allocated inside it.

3️⃣ Stack vs Heap for t_game
🎯 Recommended for cub3d: STACK
int main(void)
{
    t_game game;

    init_game(&game);
    parse(&game);
    start_graphics(&game);
    cleanup(&game);
    return (0);
}

Why stack is better here

Only one game instance exists

Lifetime = entire program

Simpler memory management

No unnecessary malloc/free

Less risk of leaks

🔥 When Does Stack Memory Disappear?

Stack variables disappear when the function returns.

❌ Wrong:

t_game *init_game(void)
{
    t_game game;
    return (&game);  // ERROR: game dies after return
}
✅ Correct: Declare in main() and pass pointer.

4️⃣ If t_game Is On Stack

You should:

Free dynamically allocated members

NOT free game itself

Example:

void cleanup(t_game *game)
{
    free_map(&game->map);
    free_textures(game);
    mlx_destroy_window(game->mlx, game->win);
}


Do NOT do:

free(game);  // ❌ wrong (stack memory)

5️⃣ If t_game Is On Heap

If allocated like this:

t_game *game = malloc(sizeof(t_game));


Then cleanup must include:

cleanup(game);
free(game);


But this is unnecessary for cub3d.

6️⃣ Initialize Everything

Always initialize your struct:

void init_game(t_game *game)
{
    ft_memset(game, 0, sizeof(t_game));
}


Why?

All pointers start as NULL

Free functions become safe

No accidental garbage values

7️⃣ Ownership Rule (Very Important)

Each allocation must have exactly ONE owner.

Example:

map owns grid

game owns map

textures owns texture paths

Never free the same memory in two different places.

8️⃣ If Struct Member Is Not Allocated

Example:

typedef struct s_game
{
    t_map map;   // NOT a pointer
} t_game;


Do NOT do:

free(game->map); // ❌ WRONG


Because map was never malloc'ed.

Only free what was dynamically allocated inside it.

9️⃣ Cleanup Order

Free in reverse order of allocation:

Destroy MLX images

Destroy window

Free textures

Free map grid

Free any remaining dynamic memory

🔟 Professional cub3d Structure Example
typedef struct s_game
{
    t_map      map;
    t_texture  textures;
    t_player   player;
    void       *mlx;
    void       *win;
} t_game;

int main(void)
{
    t_game game;

    init_game(&game);
    parse(&game);
    start_graphics(&game);
    cleanup(&game);
    return (0);
}

🧠 Final Summary

For cub3d:

✔ Keep t_game on stack
✔ Initialize with memset
✔ Free only dynamically allocated members
✔ Set freed pointers to NULL
✔ One owner per allocation
✔ Never free stack memory

This structure keeps your project clean, safe, and professional.