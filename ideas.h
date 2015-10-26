/*
 
-       neve (tabuleiro muda de cor com o tempo)
-       folhas a cair
-       sombras nas laranjas
-       esfera gigante com céu
-       densidade de cheerios igual interiores e exteriores
-       laranjas com ressalto
-       manteiga derretida, que vai aumentando (quando as gotas desaparecem)
-       manchas de manteiga que a seguem, com 10 gotas
-       init de jogo -> cheerios expandem ou caiem um a um, carro cai de cima; (efeitos sonoros!)
-       falling cheerios/ butters
-       manteigas vão girando depois de se bater lá
-       estacoes do ano
 
 */

/*
comentarios do prof
 ordenados por prioridade:
-larajas deviam ter um atributo _alive para quando "morrem" e aí é que vai ser chamado o timer, que qd acabar vai mudar o valor _alive outra vez para true metendo
 a laranja na pos 300 
-display deve desenhar apenas os objectos alive (n sei se o update tb deverá ter)
-novo timer (semelhante ao do update) no main/gamemanager para iterar laranjas e upar velocidade