#include <fcgi_stdio.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
  while (FCGI_Accept() >= 0) {
    printf("Content-type: text/html\r\n"
           "\r\n"
           "<html>\n"
           "<head>\n"
           "<title>Hello World</title>\n"
           "</head>\n"
           "<body>\n"
           "<div>Hello World!</div>\n"
           "</body>\n"
           "</html>\n");
  }
  return 0;
}
