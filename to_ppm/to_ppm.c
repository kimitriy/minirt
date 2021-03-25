//to namefile.h////////////////////////

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define TO_RED 16
#define TO_GREEN 8
#define TO_BLUE 0

typedef struct  s_image
{
   unsigned int   width;
   unsigned int   height;
   unsigned int   **canvas;
}               t_image;

//to namefile.c////////////////////

unsigned int    hex_color_to_dec(unsigned int hex_color, unsigned int color)
{
   if (color == RED)
      return ((hex_color & RED) >> TO_RED);
   else if (color == GREEN)
      return ((hex_color & GREEN) >> TO_GREEN);
   else if (color == BLUE)
      return ((hex_color & BLUE) >> TO_BLUE);
   else
      return (0);
}

int     to_file(t_image image)
{
   int             fd;
   unsigned int   count_width = 0;
   unsigned int   count_height = 0;
   if (-1 == (fd = open("/Users/mscot/Documents/42cursus/03_level/28012020_minirt/image.ppm", O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0644)))
      return (1);
   dprintf(fd, "P3 %d %d\n", image.width, image.height);
   dprintf(fd, "%d\n", 255);
   while (count_height < image.height)
   {
      while (count_width < image.width)
      {
         dprintf(fd, "%u %u %u ",
               hex_color_to_dec(image.canvas[count_height][count_width], RED),
               hex_color_to_dec(image.canvas[count_height][count_width], GREEN),
               hex_color_to_dec(image.canvas[count_height][count_width], BLUE)
         );
         count_width++;
      }
      dprintf(fd, "\n");
      count_width = 0;
      count_height++;
   }
   return (1);
}