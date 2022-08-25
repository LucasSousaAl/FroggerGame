#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>  
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

//VARIAVEIS GLOBAIS

int contador = 0;
int nivel = 0;
long largura = 727;
long altura = 808 + 75;
int ky = 0;

int score = 0;
int flags = 0;
float speed = 1.0;
int mortes = 0;
double contadorfim = 0;

void must_init(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void fundo(ALLEGRO_BITMAP* cen, ALLEGRO_FONT* font,int score) {
    
    al_draw_bitmap(cen, 0, 0, 0);
    al_draw_line(0, 620, 80, 620, al_map_rgb_f(100, 100, 100), 3);
    al_draw_line(0, 749, 80, 749, al_map_rgb_f(100, 100, 100), 3);

    al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 15, 0, "Score: %d",score);
 
}

void morreu(ALLEGRO_BITMAP* morte,int x ,int y, ALLEGRO_SAMPLE* batida) {
    al_convert_mask_to_alpha(morte, al_map_rgb_f(0, 0, 0));
    al_draw_bitmap(morte, x, y, 0);
    al_play_sample(batida, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    mortes++;
}

int main() {
    boolean fim0 = false;
    boolean fim1 = false;
    boolean fim2 = false;
    boolean fim3 = false;
    boolean fim4 = false;
    boolean gameover = false;
    boolean starter = false;

    //Posicoes dos objetos que se movimentao
    int xx = 0;
    int x1 = 0;
    int x2 = -220;
    int x3 = 602;
    int x4 = 1100;
    int x5 = 602;
    int x6 = 0;
    int x7 = -50;
    int x8 = -120;
    int x9 = -450;
    int x20 = -450 + 68;
    int x10 = -450;
    int x11 = largura; //t
    int x12 = largura + 68; //t
    int x13 = largura + 136;  //tartaruga esquerda
    int x14 = largura + 136; // tora 4
    int x15 = largura + 136 + 450; // tora 5
    int x16 = 0; // tora 6
    int x17 = 400; // tora 7
    int x18 = largura + 400;
    int x19 = largura + 468;
    int x21 = largura + 468 + 68;
    

    must_init(al_init(), "allegro");
    al_install_keyboard();
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(727, 875);
    must_init(disp, "display");

    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_init_font_addon(), "font");
    must_init(al_init_ttf_addon(), "ttf");

    //-----------------audio--------------------------
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");

    //--------------TRILHA SONORA--------------------
    ALLEGRO_SAMPLE* music1 = al_load_sample("audio/music1.wav");
    must_init(music1, "music1");
    ALLEGRO_SAMPLE_INSTANCE* inst_music1 = NULL;
    inst_music1 = al_create_sample_instance(music1);

    ALLEGRO_SAMPLE* pulo = al_load_sample("audio/pulo.mp3");
    must_init(pulo, "pulo");

    ALLEGRO_SAMPLE* batida = al_load_sample("audio/batida.mp3");
    must_init(batida, "batida");
  
    ALLEGRO_SAMPLE* agua = al_load_sample("audio/agua.mp3");
    must_init(agua, "agua");
    ALLEGRO_SAMPLE* casinha = al_load_sample("audio/casinha.mp3");
    must_init(casinha, "casinha");
    ALLEGRO_SAMPLE* newnivel = al_load_sample("audio/newnivel.mp3");
    must_init(newnivel, "newnivel");

    ALLEGRO_FONT* font = al_load_font("font/arial.ttf", 30, 0);
    must_init(font, "font");

    ALLEGRO_FONT* font2 = al_load_font("font/arial.ttf", 20, 0);
    must_init(font2, "font2");
    must_init(al_init_image_addon(), "image addon");
   
    ALLEGRO_BITMAP* cenarionovo = al_load_bitmap("images/cenarionovo.png");
    must_init(cenarionovo, "cenarionovo");
    ALLEGRO_BITMAP* inicial = al_load_bitmap("images/inicial.png");
    must_init(inicial, "inicial");
    ALLEGRO_BITMAP* gameoverimg = al_load_bitmap("images/gameover.png");
    must_init(gameoverimg, "gameoverimg");

    //----------------------------Veiculos-------------------------
    ALLEGRO_BITMAP* caminhao = al_load_bitmap("images/caminhao.png");
    must_init(caminhao, "caminhao");
    ALLEGRO_BITMAP* carro1 = al_load_bitmap("images/carro 1.png");
    must_init(carro1, "carro1");
    ALLEGRO_BITMAP* carro2 = al_load_bitmap("images/carro2.png");
    must_init(carro2, "carro2");
    ALLEGRO_BITMAP* carro3 = al_load_bitmap("images/carro3.png");
    must_init(carro3, "carro3");

    //----------------------Sapos---------------------------
    ALLEGRO_BITMAP* sapofim = al_load_bitmap("images/sapofim.png");
    must_init(sapofim, "sapofim");
    ALLEGRO_BITMAP* sapo1 = al_load_bitmap("images/sapo1.png");
    must_init(sapo1, "sapo1");
    ALLEGRO_BITMAP* sapoaux = al_load_bitmap("images/sapo1.png");
    must_init(sapoaux, "sapoaux");
    ALLEGRO_BITMAP* sapoe = al_load_bitmap("images/sapoe.png");
    must_init(sapoe, "sapoe");
    ALLEGRO_BITMAP* sapoup = al_load_bitmap("images/sapoup.png");
    must_init(sapoup, "sapoup");
    ALLEGRO_BITMAP* saporigth = al_load_bitmap("images/saporigth.png");
    must_init(saporigth, "saporigth");
    ALLEGRO_BITMAP* life = al_load_bitmap("images/life.png");
    must_init(life, "life");
    ALLEGRO_BITMAP* turtles = al_load_bitmap("images/turtles.png");
    must_init(turtles, "turtles");

    //-----------------------Toras----------------------
    ALLEGRO_BITMAP* tora1 = al_load_bitmap("images/tora1.png");
    must_init(tora1, "tora1");
    ALLEGRO_BITMAP* tora2 = al_load_bitmap("images/tora2.png");
    must_init(tora2, "tora2");
    ALLEGRO_BITMAP* morte = al_load_bitmap("images/morte.png");
    must_init(morte, "morte");

    //-------------------tartarugas----------------------
    ALLEGRO_BITMAP* sprite = al_load_bitmap("images/sprite.png");
    must_init(sprite, "sprite");
    ALLEGRO_BITMAP* tartaruga1 = al_load_bitmap("images/tartaruga1.png");
    must_init(tartaruga1, "tartaruga1");
    ALLEGRO_BITMAP* tartaruga2 = al_load_bitmap("images/tartaruga2.png");
    must_init(tartaruga2, "tartaruga2");
    ALLEGRO_BITMAP* tartaruga3 = al_load_bitmap("images/tartaruga3.png");
    must_init(tartaruga3, "tartaruga3");


    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    int x, y;
    x = (largura/2)-28;
    y = altura-65;
    int xfim0 = 20, xfim1 = 177, xfim2 = 335,xfim3=490,xfim4=649;
    float speed2 = 0;

#define KEY_SEEN     1
#define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    //------------------Colocando a musica para tocar-------------------
    al_attach_sample_instance_to_mixer(inst_music1, al_get_default_mixer());
    al_set_sample_instance_playmode(inst_music1, ALLEGRO_PLAYMODE_LOOP);  

    al_start_timer(timer);
    while (1)
    {            
            al_wait_for_event(queue, &event);
            switch (event.type)
            {
            case ALLEGRO_EVENT_TIMER:


               


                if (!gameover && starter) {
                   
                    fundo(cenarionovo, font, score);
                    if (nivel == 0) {
                        al_set_sample_instance_gain(inst_music1, 0.7);
                        al_set_sample_instance_speed(inst_music1, 1.0);
                        al_play_sample_instance(inst_music1);
                    }
                    
                    //-------------------Casas do sapo e nivel novo---------------
                    if (fim0) {
                        al_convert_mask_to_alpha(sapofim, al_map_rgb_f(0, 0, 0));
                        al_draw_bitmap(sapofim, xfim0, 105, 0);
                    }
                    if (fim1) {
                        al_convert_mask_to_alpha(sapofim, al_map_rgb_f(0, 0, 0));
                        al_draw_bitmap(sapofim, xfim1, 105, 0);
                    }
                    if (fim2) {
                        al_convert_mask_to_alpha(sapofim, al_map_rgb_f(0, 0, 0));
                        al_draw_bitmap(sapofim, xfim2, 105, 0);
                    }
                    if (fim3) {
                        al_convert_mask_to_alpha(sapofim, al_map_rgb_f(0, 0, 0));
                        al_draw_bitmap(sapofim, xfim3, 105, 0);
                    }
                    if (fim4) {
                        al_convert_mask_to_alpha(sapofim, al_map_rgb_f(0, 0, 0));
                        al_draw_bitmap(sapofim, xfim4, 105, 0);
                    }
                    //-------------------VIDAS DO SAPO---------------------------
                    if (mortes == 0) {
                        al_convert_mask_to_alpha(life, al_map_rgb(0, 0, 0));
                        al_draw_bitmap(life, 550, 15, 0);
                        al_convert_mask_to_alpha(life, al_map_rgb(0, 0, 0));
                        al_draw_bitmap(life, 600, 15, 0);
                        al_convert_mask_to_alpha(life, al_map_rgb(0, 0, 0));
                        al_draw_bitmap(life, 650, 15, 0);

                    }
                    else if (mortes == 1) {
                        al_convert_mask_to_alpha(life, al_map_rgb(0, 0, 0));
                        al_draw_bitmap(life, 550, 15, 0);
                        al_convert_mask_to_alpha(life, al_map_rgb(0, 0, 0));
                        al_draw_bitmap(life, 600, 15, 0);
                    }
                    else if (mortes == 2) {
                        al_convert_mask_to_alpha(life, al_map_rgb(0, 0, 0));
                        al_draw_bitmap(life, 550, 15, 0);
                    }
                    else if (mortes == 3) {
                        gameover = true;                     
                    }
                    //--------------------Subindo de nivel----------------------------
                    if ((fim0 == true) && (fim1 == true) && (fim2 == true) && (fim3 == true) && (fim4 == true)) {
                     //if (fim1 == true) {
                        score += 1000;
                        fim0 = false;
                        fim1 = false;
                        fim2 = false;
                        fim3 = false;
                        fim4 = false;
                        if (speed <= 1.8) {
                            speed += 0.15;
                            speed2 += 0.7;
                        }

                        al_play_sample(newnivel, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        al_set_sample_instance_speed(inst_music1, speed);
                        nivel += 1;
                    }
                    //---------------------------Veiculos--------------------------
                    al_draw_bitmap(caminhao, xx += 3, 553, 0);
                    al_convert_mask_to_alpha(caminhao, al_map_rgb_f(0, 0, 0));
                    al_draw_bitmap(carro1, x1 += 6 + (speed2 * 1.6), 618, 0);
                    al_draw_bitmap(carro1, x2 += 6 + (speed2 * 1.6), 618, 0);
                    al_convert_mask_to_alpha(carro1, al_map_rgb_f(0, 0, 0));

                    al_draw_bitmap(carro2, x3 -= 5, 684, 0);
                    al_draw_bitmap(carro2, x4 -= 5, 684, 0);
                    al_convert_mask_to_alpha(carro2, al_map_rgb_f(0, 0, 0));

                    al_draw_bitmap(carro3, x5 -= 5 + speed2, 755, 0);
                    al_convert_mask_to_alpha(carro3, al_map_rgb_f(0, 0, 0));

                    //-------------------------toras--------------------------------
                    al_draw_bitmap(tora1, x6 += 5 + speed2, 360, 0);
                    al_convert_mask_to_alpha(tora1, al_map_rgb_f(0, 0, 0));

                    al_draw_bitmap(tora1, x15 -= 5 + speed2, 293, 0);
                    al_convert_mask_to_alpha(tora1, al_map_rgb_f(0, 0, 0));

                    al_draw_bitmap(tora2, x10 += 5 + speed2, 360, 0);
                    al_convert_mask_to_alpha(tora2, al_map_rgb_f(0, 0, 0));

                    al_draw_bitmap(tora2, x14 -= 5 + speed2, 293, 0);
                    al_convert_mask_to_alpha(tora2, al_map_rgb_f(0, 0, 0));

                    al_draw_bitmap(tora2, x16 += 6 + speed2, 160, 0);
                    al_convert_mask_to_alpha(tora2, al_map_rgb_f(0, 0, 0));

                    al_draw_bitmap(tora2, x17 += 6 + speed2, 160, 0);
                    al_convert_mask_to_alpha(tora2, al_map_rgb_f(0, 0, 0));

                    //--------------TARTARUGAS DESENHO E ANIMACAO ------------------  
                    if (nivel < 1) {
                        if (contador <= 20) {
                            al_convert_mask_to_alpha(tartaruga1, al_map_rgb_f(0, 0, 0));
                            al_draw_bitmap(tartaruga1, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga1, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga1, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga1, x20 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga1, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga1, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga1, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga1, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga1, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga1, x21 -= 4, 150 + 75, 1);



                        }
                        else if (contador <= 35) {
                            al_convert_mask_to_alpha(tartaruga3, al_map_rgb_f(0, 0, 0));
                            al_draw_bitmap(tartaruga3, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga3, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga3, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga3, x20 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga3, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga3, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga3, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga3, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga3, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga3, x21 -= 4, 150 + 75, 1);

                        }
                        else if (contador <= 40) {
                            al_convert_mask_to_alpha(tartaruga2, al_map_rgb_f(0, 0, 0));
                            al_draw_bitmap(tartaruga2, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga2, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga2, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga2, x20 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga2, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga2, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga2, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga2, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga2, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga2, x21 -= 4, 150 + 75, 1);

                        }
                        else {
                            al_convert_mask_to_alpha(tartaruga2, al_map_rgb_f(0, 0, 0));
                            al_draw_bitmap(tartaruga2, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga2, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga2, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga2, x20 += 4, 345 + 75, 0);
                            al_draw_bitmap(tartaruga2, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga2, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga2, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga2, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga2, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap(tartaruga2, x21 -= 4, 150 + 75, 1);

                            contador = 5;
                        }
                    }
                    else {

                        al_convert_mask_to_alpha(turtles, al_map_rgb_f(0, 0, 0));
                        al_convert_mask_to_alpha(turtles, al_map_rgb_f(0, 0, 0));

                        if (contador <= 10) {
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);

                        }
                        else if (contador > 10 && contador <= 20) {
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        else if (contador > 20 && contador <= 30) {
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        else if (contador > 30 && contador <= 40) {
                            al_draw_bitmap_region(turtles, 228, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 228, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 228, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 228, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 228, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        else if (contador > 40 && contador <= 50) {
                            al_draw_bitmap_region(turtles, 304, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 304, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 304, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 304, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 304, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        else if (contador > 50 && contador <= 60) {
                            al_draw_bitmap_region(turtles, 380, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 380, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 380, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 380, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 380, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        else if (contador > 60 && contador <= 70) {
                            al_draw_bitmap_region(turtles, 456, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 456, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 456, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 456, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 456, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        else if (contador > 70 && contador <= 80) {
                            al_draw_bitmap_region(turtles, 532, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 532, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 532, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 532, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 532, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        else if (contador > 80 && contador <= 90) {
                            al_draw_bitmap_region(turtles, 603, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 603, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 603, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 603, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 603, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        else if (contador > 90 && contador <= 100) {
                            al_draw_bitmap_region(turtles, 679, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 679, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 679, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 679, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 679, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        else if (contador > 100 && contador <= 110) {
                            al_draw_bitmap_region(turtles, 780, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 780, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 780, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 780, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 780, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        else if (contador > 110 && contador <= 120) {
                            al_draw_bitmap_region(turtles, 780, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 780, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 780, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 780, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 780, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        else if (contador > 120 && contador <= 130) {
                            al_draw_bitmap_region(turtles, 679, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 679, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 0, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 679, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 679, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 679, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        else if (contador > 130 && contador <= 140) {
                            al_draw_bitmap_region(turtles, 603, 0, (74.5), 76, x7 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 603, 0, (74.5), 76, x8 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x9 += 4, 345 + 75, 0);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x20 += 4, 345 + 75, 0);

                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x11 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x12 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 152, 0, (74.5), 76, x13 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 603, 0, (74.5), 76, x18 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 603, 0, (74.5), 76, x19 -= 4, 150 + 75, 1);
                            al_draw_bitmap_region(turtles, 603, 0, (74.5), 76, x21 -= 4, 150 + 75, 1);
                        }
                        if (contador >= 140)
                            contador = 0;

                    }
                    //--------------------MOVIMEMENTO DO SAPO--------------------------                
                    if (key[ALLEGRO_KEY_UP] && ky == 0) {

                        al_convert_mask_to_alpha(sapoup, al_map_rgb_f(0, 0, 0));
                        al_draw_bitmap(sapoup, x, y, 0);
                        al_play_sample(pulo, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    else if (key[ALLEGRO_KEY_DOWN] && ky == 0) {
                        al_convert_mask_to_alpha(sapoup, al_map_rgb_f(0, 0, 0));
                        al_draw_bitmap(sapoup, x, y, 2);
                        al_play_sample(pulo, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    else if (key[ALLEGRO_KEY_RIGHT] && ky == 0) {
                        al_convert_mask_to_alpha(saporigth, al_map_rgb_f(0, 0, 0));
                        al_draw_bitmap(saporigth, x, y, 0);
                        al_play_sample(pulo, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    else if (key[ALLEGRO_KEY_LEFT] && ky == 0) {
                        al_convert_mask_to_alpha(saporigth, al_map_rgb_f(0, 0, 0));
                        al_draw_bitmap(saporigth, x, y, 1);
                        al_play_sample(pulo, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    else {
                        al_convert_mask_to_alpha(sapo1, al_map_rgb_f(0, 0, 0));
                        al_draw_bitmap(sapo1, x, y, flags);


                    }

                    //-------------------COLISAO DOS CARROS-----------------------------
                    if ((x >= xx) && (x <= xx + 278) && (y >= 470 + 75) && (y <= 540 + 75)) {
                        morreu(morte, x, y + 75, batida);
                        x = (largura / 2) - 28;
                        y = altura - 65;
                    }

                    if ((x >= x5 - 30) && (x <= x5 + 170) && (y >= 660 + 75) && (y <= 720 + 75)) {
                        morreu(morte, x, y, batida);
                        x = (largura / 2) - 28;
                        y = altura - 65;
                    }

                    if ((x >= x1) && (x <= x1 + 118) && (y >= 534 + 75) && (y <= 609 + 75)) {
                        morreu(morte, x, y, batida);
                        x = (largura / 2) - 28;
                        y = altura - 65;
                    }
                    if ((x >= x2) && (x <= x2 + 118) && (y >= 534 + 75) && (y <= 609 + 75)) {
                        morreu(morte, x, y, batida);
                        x = (largura / 2) - 28;
                        y = altura - 65;
                    }
                    if ((x >= x3 - 20) && (x <= x3 + 118) && (y >= 600 + 75) && (y <= 675 + 75)) {
                        morreu(morte, x, y, batida);
                        x = (largura / 2) - 28;
                        y = altura - 65;
                    }
                    if ((x >= x4 - 20) && (x <= x4 + 118) && (y >= 600 + 75) && (y <= 675 + 75)) {
                        morreu(morte, x, y, batida);
                        x = (largura / 2) - 28;
                        y = altura - 65;
                    }

                    //-----------------------Colisao das toras e tartaruga--------------

                    //tora
                    if (nivel < 1) {
                        if ((x >= x7 - 30) && (x <= x7 + 70) && (y >= 350 + 75) && (y <= 406 + 75)) {
                            x = x7 + 10;
                            x += 4;
                        }
                        else if ((x >= x20 - 30) && (x <= x20 + 70) && (y >= 350 + 75) && (y <= 406 + 75)) {
                            x = x20 + 10;
                            x += 4;
                        }
                        else if ((x >= x8 - 30) && (x <= x8 + 70) && (y >= 350 + 75) && (y <= 406 + 75)) {
                            x = x8 + 10;
                            x += 4;
                        }
                        else if ((x >= x9 - 30) && (x <= x9 + 73) && (y >= 350 + 75) && (y <= 406 + 75)) {
                            x = x9 + 10;
                            x += 4;
                        }
                        else if ((x >= x11 - 15) && (x <= x11 + 75) && (y >= 225) && (y <= 293)) {
                            x = x11 + 10;
                            x -= 4;
                        }
                        else if ((x >= x12 - 15) && (x <= x12 + 75) && (y >= 225) && (y <= 293)) {
                            x = x12 + 10;
                            x -= 4;
                        }
                        else if ((x >= x13 - 15) && (x <= x13 + 70) && (y >= 225) && (y <= 293)) {
                            x = x13 + 20;
                            x -= 4;
                        }

                        else if ((x >= x18 - 15) && (x <= x18 + 75) && (y >= 225) && (y <= 293)) {
                            x = x18 + 10;
                            x -= 4;
                        }
                        else if ((x >= x19 - 15) && (x <= x19 + 70) && (y >= 225) && (y <= 293)) {
                            x = x19 + 20;
                            x -= 4;
                        }
                        else if ((x >= x21 - 15) && (x <= x21 + 70) && (y >= 225) && (y <= 293)) {
                            x = x21 + 20;
                            x -= 4;
                        }



                        else if ((x >= x6 - 30) && (x <= x6 + 271) && (y >= 360) && (y <= 420)) {
                            x += 5 + speed2;
                        }
                        else if ((x >= x10 - 15) && (x <= x10 + 180) && (y >= 360) && (y <= 420)) {
                            x += 5 + speed2;
                        }
                        else if ((x >= x14 - 15) && (x <= x14 + 180) && (y >= 293) && (y <= 360)) {
                            x -= 5 + speed2;
                        }
                        else if ((x >= x15 - 15) && (x <= x15 + 271) && (y >= 293) && (y <= 360)) {
                            x -= 5 + speed2;
                        }
                        else if ((x >= x16 - 15) && (x <= x16 + 180) && (y >= 160) && (y <= 230)) {
                            x += 6 + speed2;
                        }
                        else if ((x >= x17 - 15) && (x <= x17 + 180) && (y >= 160) && (y <= 230)) {
                            x += 6 + speed2;
                        }
                        else if ((x >= x6 - 30) && (x <= x6 + 271) && (y >= 360) && (y <= 420)) {
                            x += 5 + speed2;
                        }
                        else if ((x >= x10 - 15) && (x <= x10 + 180) && (y >= 360) && (y <= 420)) {
                            x += 5 + speed2;
                        }
                        else if ((x >= x14 - 15) && (x <= x14 + 180) && (y >= 293) && (y <= 360)) {
                            x -= 5 + speed2;
                        }
                        else if ((x >= x15 - 15) && (x <= x15 + 271) && (y >= 293) && (y <= 360)) {
                            x -= 5 + speed2;
                        }
                        else if ((x >= x16 - 15) && (x <= x16 + 180) && (y >= 160) && (y <= 230)) {
                            x += 6 + speed2;
                        }
                        else if ((x >= x17 - 15) && (x <= x17 + 180) && (y >= 160) && (y <= 230)) {
                            x += 6 + speed2;
                        }


                        else if (((x >= xfim0 - 15) && (x <= xfim0 + 70) && (y <= 145))) {
                            x = (largura / 2) - 28;
                            y = altura - 65;
                            al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            score += 200;
                            fim0 = true;

                        }
                        else if ((x >= xfim1 - 15) && (x <= xfim1 + 70) && (y <= 145)) {
                            x = (largura / 2) - 28;
                            y = altura - 65;
                            al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            score += 200;
                            fim1 = true;
                        }
                        else if ((x >= xfim2 - 15) && (x <= xfim2 + 70) && (y <= 145)) {
                            x = (largura / 2) - 28;
                            y = altura - 65;
                            al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            score += 200;
                            fim2 = true;
                        }
                        else if ((x >= xfim3 - 15) && (x <= xfim3 + 70) && (y <= 145)) {
                            x = (largura / 2) - 28;
                            y = altura - 65;
                            al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            score += 200;
                            fim3 = true;
                        }
                        else if ((x >= xfim4 - 15) && (x <= xfim4 + 75) && (y <= 145)) {
                            x = (largura / 2) - 28;
                            y = altura - 65;
                            al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            score += 200;
                            fim4 = true;
                        }
                        else if (y <= 478 && y >= 90) {
                            morreu(morte, x, y, agua);
                            x = (largura / 2) - 28;
                            y = altura - 65;
                        }
                    }
                    else {
                        if (contador < 100) 
                        {
                            if ((x >= x7 - 15) && (x <= x7 + 70) && (y >= 350 + 75) && (y <= 406 + 75)) {
                                x = x7 + 10;
                                x += 4;
                            }

                            else if ((x >= x8 - 15) && (x <= x8 + 70) && (y >= 350 + 75) && (y <= 406 + 75)) {
                                x = x8 + 10;
                                x += 4;
                            }

                            else if ((x >= x18 - 15) && (x <= x18 + 75) && (y >= 225) && (y <= 293)) {
                                x = x18 + 10;
                                x -= 4;
                            }
                            else if ((x >= x19 - 15) && (x <= x19 + 70) && (y >= 225) && (y <= 293)) {
                                x = x19 + 20;
                                x -= 4;
                            }
                            else if ((x >= x21 - 15) && (x <= x21 + 70) && (y >= 225) && (y <= 293)) {
                                x = x21 + 20;
                                x -= 4;
                            }

                            else if ((x >= x9 - 15) && (x <= x9 + 73) && (y >= 350 + 75) && (y <= 406 + 75)) {
                                x = x9 + 10;
                                x += 4;
                            }
                            else if ((x >= x20 - 15) && (x <= x20 + 70) && (y >= 350 + 75) && (y <= 406 + 75)) {
                                x = x20 + 10;
                                x += 4;
                            }

                            else if ((x >= x11 - 15) && (x <= x11 + 75) && (y >= 225) && (y <= 293)) {
                                x = x11 + 10;
                                x -= 4;
                            }
                            else if ((x >= x12 - 15) && (x <= x12 + 75) && (y >= 225) && (y <= 293)) {
                                x = x12 + 10;
                                x -= 4;
                            }
                            else if ((x >= x13 - 15) && (x <= x13 + 70) && (y >= 225) && (y <= 293)) {
                                x = x13 + 20;
                                x -= 4;
                            }
                            else if ((x >= x6 - 30) && (x <= x6 + 271) && (y >= 360) && (y <= 420)) {
                                x += 5 + speed2;
                            }
                            else if ((x >= x10 - 15) && (x <= x10 + 180) && (y >= 360) && (y <= 420)) {
                                x += 5 + speed2;
                            }
                            else if ((x >= x14 - 15) && (x <= x14 + 180) && (y >= 293) && (y <= 360)) {
                                x -= 5 + speed2;
                            }
                            else if ((x >= x15 - 15) && (x <= x15 + 271) && (y >= 293) && (y <= 360)) {
                                x -= 5 + speed2;
                            }
                            else if ((x >= x16 - 15) && (x <= x16 + 180) && (y >= 160) && (y <= 230)) {
                                x += 6 + speed2;
                            }
                            else if ((x >= x17 - 15) && (x <= x17 + 180) && (y >= 160) && (y <= 230)) {
                                x += 6 + speed2;
                            }
                            else if (((x >= xfim0 - 15) && (x <= xfim0 + 70) && (y <= 145))) {
                                x = (largura / 2) - 28;
                                y = altura - 65;
                                al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                score += 200;
                                fim0 = true;

                            }
                            else if ((x >= xfim1 - 15) && (x <= xfim1 + 70) && (y <= 145)) {
                                x = (largura / 2) - 28;
                                y = altura - 65;
                                al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                score += 200;
                                fim1 = true;
                            }
                            else if ((x >= xfim2 - 15) && (x <= xfim2 + 70) && (y <= 145)) {
                                x = (largura / 2) - 28;
                                y = altura - 65;
                                al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                score += 200;
                                fim2 = true;
                            }
                            else if ((x >= xfim3 - 15) && (x <= xfim3 + 70) && (y <= 145)) {
                                x = (largura / 2) - 28;
                                y = altura - 65;
                                al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                score += 200;
                                fim3 = true;
                            }
                            else if ((x >= xfim4 - 15) && (x <= xfim4 + 75) && (y <= 145)) {
                                x = (largura / 2) - 28;
                                y = altura - 65;
                                al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                score += 200;
                                fim4 = true;
                            }
                            else if (y <= 478 && y >= 90) {
                                morreu(morte, x, y, agua);
                                x = (largura / 2) - 28;
                                y = altura - 65;
                            }
                        }

                        else if ((x >= x9 - 15) && (x <= x9 + 73) && (y >= 350 + 75) && (y <= 406 + 75)) {
                            x = x9 + 10;
                            x += 4;
                        }
                        else if ((x >= x20 - 15) && (x <= x20 + 70) && (y >= 350 + 75) && (y <= 406 + 75)) {
                            x = x20 + 10;
                            x += 4;
                        }

                        else if ((x >= x11 - 15) && (x <= x11 + 75) && (y >= 225) && (y <= 293)) {
                            x = x11 + 10;
                            x -= 4;
                        }
                        else if ((x >= x12 - 15) && (x <= x12 + 75) && (y >= 225) && (y <= 293)) {
                            x = x12 + 10;
                            x -= 4;
                        }
                        else if ((x >= x13 - 15) && (x <= x13 + 70) && (y >= 225) && (y <= 293)) {
                            x = x13 + 20;
                            x -= 4;
                        }

                        else if ((x >= x6 - 30) && (x <= x6 + 271) && (y >= 360) && (y <= 420)) {
                            x += 5 + speed2;
                        }
                        else if ((x >= x10 - 15) && (x <= x10 + 180) && (y >= 360) && (y <= 420)) {
                            x += 5 + speed2;
                        }
                        else if ((x >= x14 - 15) && (x <= x14 + 180) && (y >= 293) && (y <= 360)) {
                            x -= 5 + speed2;
                        }
                        else if ((x >= x15 - 15) && (x <= x15 + 271) && (y >= 293) && (y <= 360)) {
                            x -= 5 + speed2;
                        }
                        else if ((x >= x16 - 15) && (x <= x16 + 180) && (y >= 160) && (y <= 230)) {
                            x += 6 + speed2;
                        }
                        else if ((x >= x17 - 15) && (x <= x17 + 180) && (y >= 160) && (y <= 230)) {
                            x += 6 + speed2;
                        }


                        else if (((x >= xfim0 - 15) && (x <= xfim0 + 70) && (y <= 145))) {
                            x = (largura / 2) - 28;
                            y = altura - 65;
                            al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            score += 200;
                            fim0 = true;

                        }
                        else if ((x >= xfim1 - 15) && (x <= xfim1 + 70) && (y <= 145)) {
                            x = (largura / 2) - 28;
                            y = altura - 65;
                            al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            score += 200;
                            fim1 = true;
                        }
                        else if ((x >= xfim2 - 15) && (x <= xfim2 + 70) && (y <= 145)) {
                            x = (largura / 2) - 28;
                            y = altura - 65;
                            al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            score += 200;
                            fim2 = true;
                        }
                        else if ((x >= xfim3 - 15) && (x <= xfim3 + 70) && (y <= 145)) {
                            x = (largura / 2) - 28;
                            y = altura - 65;
                            al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            score += 200;
                            fim3 = true;
                        }
                        else if ((x >= xfim4 - 15) && (x <= xfim4 + 75) && (y <= 145)) {
                            x = (largura / 2) - 28;
                            y = altura - 65;
                            al_play_sample(casinha, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            score += 200;
                            fim4 = true;
                        }
                        else if (y <= 478 && y >= 90) {
                            morreu(morte, x, y, agua);
                            x = (largura / 2) - 28;
                            y = altura - 65;
                        }
                    }



                    if (xx > largura) {
                        xx = -300;
                    }
                    if (x1 > largura) {
                        x1 = -250;
                    }
                    if (x2 > largura) {
                        x2 = -250;
                    }
                    if (x3 < -100) {
                        x3 = 800;
                    }
                    if (x4 < -100) {
                        x4 = 800;
                    }
                    if (x5 < -170) {
                        x5 = 800;
                    }

                    if (x6 > largura) {
                        x6 = -250;
                    }
                    if (x7 > largura) {
                        x7 = -250;
                    }
                    if (x8 > largura) {
                        x8 = -250;
                    }
                    if (x9 > largura) {
                        x9 = -260;
                    }
                    if (x10 > largura) {
                        x10 = -250;
                    }
                    if (x11 <= -210) {
                        x11 = largura;
                    }
                    if (x12 < -140) {
                        x12 = largura + 70;
                    }
                    if (x13 < -70) {
                        x13 = largura + 140;
                    }

                    if (x14 < -260) {
                        x14 = largura;
                    }

                    if (x15 < -260) {
                        x15 = largura;
                    }
                    if (x16 > largura) {
                        x16 = -180;
                    }
                    if (x17 > largura) {
                        x17 = -180;
                    }

                    if (x19 < -140) {
                        x19 = largura + 70;
                    }
                    if (x18 < -70) {
                        x18 = largura + 140;
                    }
                    if (x20 > largura) {
                        x20 = -260;
                    }
                    if (x21 < -70) {
                        x21 = largura + 140;
                    }

                    al_flip_display();

                    if (x <= 0) {
                        x = 25;
                    }
                    if (x >= largura - 60) {
                        x = largura - 80;
                    }
                    if (y >= altura - 60) {
                        y = altura - 60;
                    }
                    if (y >= altura - 60 && x <= 0) {
                        x = 0;
                        y = altura - 60;
                    }

                    if (key[ALLEGRO_KEY_UP] && ky == 0) {
                        y = y - 65;
                        flags = 0;
                        sapo1 = sapoaux;
                    }

                    if (key[ALLEGRO_KEY_DOWN] && ky == 0) {
                        y = y + 65;
                        flags = 2;
                        sapo1 = sapoaux;
                    }
                    if (key[ALLEGRO_KEY_LEFT] && ky == 0) {
                        x = x - 78;
                        flags = 0;
                        sapo1 = sapoe;
                    }
                    if (key[ALLEGRO_KEY_RIGHT] && ky == 0) {
                        x = x + 78;
                        sapo1 = sapoe;
                        flags = ALLEGRO_FLIP_HORIZONTAL;
                        
                    }

                    if (key[ALLEGRO_KEY_ESCAPE])
                        done = true;
                    for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                        key[i] &= KEY_SEEN;

                    if (!(key[ALLEGRO_KEY_UP] || key[ALLEGRO_KEY_LEFT] || key[ALLEGRO_KEY_RIGHT] || key[ALLEGRO_KEY_DOWN])) {
                        ky = 0;

                    }
                    else ky = 1;

                }
                //----------------------------GAME-OVER---------------------------------------
               else if(gameover && starter) {
                      al_draw_rectangle(300, 300, 300, 300, al_map_rgb_f(0, 0, 0), 1500);
                      al_convert_mask_to_alpha(gameoverimg, al_map_rgb(0, 0, 0));
                      al_draw_bitmap(gameoverimg, 170, 250, 0);
                      al_stop_sample_instance(inst_music1);
                      if (contadorfim <= 15) {
                        al_draw_text(font2, al_map_rgb(255, 255, 255), 100, 600, 0, " SPACE para jogar novamente e ESC para sair do jogo ...");
                      }else if(contadorfim> 30)
                      contadorfim = 0;

                      al_flip_display();


                      if (key[ALLEGRO_KEY_SPACE]) {
                      mortes = 0;
                       nivel = 0;
                       speed = 1.0;   
                       score = 0;
                       fim0 = false;
                       fim1 = false;
                       fim2 = false;
                       fim3 = false;
                       fim4 = false;
                       gameover = false;
                       starter = false;
                       }
                    if (key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                    contadorfim++;
                  }
               else {          
              
              
               al_draw_bitmap(inicial, -2, 0, 0);
               al_stop_sample_instance(inst_music1);
               if (contadorfim <= 15) {
                   al_draw_text(font2, al_map_rgb(255, 255, 255), 250, 700, 0, " SPACE para iniciar...");
               }
               else if (contadorfim > 30)
                   contadorfim = 0;

               al_flip_display();


               if (key[ALLEGRO_KEY_SPACE]) {
                   starter = true;
               }
               if (key[ALLEGRO_KEY_ESCAPE])
                   done = true;

               contadorfim++;
                }

                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            }

            if (done)
                break;

            if (redraw && al_is_event_queue_empty(queue))
            {

                redraw = false;
            }
            contador++;      
    }
    //-----------------------Finalizacoes--------------------------------------
    al_destroy_bitmap(cenarionovo);
    al_destroy_bitmap(sapo1);
    al_destroy_bitmap(saporigth);
    al_destroy_bitmap(sapoup);
    al_destroy_bitmap(life);
    al_destroy_bitmap(tartaruga1);
    al_destroy_bitmap(tartaruga2);
    al_destroy_bitmap(tartaruga3);
    al_destroy_bitmap(tora1);
    al_destroy_bitmap(tora2);
    al_destroy_bitmap(turtles);
    al_destroy_bitmap(caminhao);
    al_destroy_bitmap(carro1);
    al_destroy_bitmap(carro2);
    al_destroy_bitmap(carro3);
    al_destroy_bitmap(sprite);
    al_destroy_bitmap(gameoverimg);
    al_destroy_font(font);
    al_destroy_font(font2);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_sample(music1);
    al_destroy_sample(pulo);
    al_destroy_sample(batida);
    al_destroy_sample(agua);
    al_destroy_sample(casinha);
    al_destroy_sample(newnivel);
      
    return 0;
}

