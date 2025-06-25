const TMDB_ENDPOINT_BASE = 'https://api.themoviedb.org/3';

//cria cards dos filmes pupulares
function Expandido(endp,i){
  //executar AJAX
  
  $.ajax({
      // Passar a URL ENDPOINT BASE + /movie/popular
      url: TMDB_ENDPOINT_BASE + '/movie/'+ endp,
      data: {
          api_key: 'c2f4c89b537808c194cac27dae3a091e'
      }
  })
      
  // Receber o JSON
  .done(function (data) {
  
      let codigo_html = '';
      let titulo_html = "";
        titulo_html += `<h1 class="lançamento" >FILMES POPULARES</h1>`;
      // Montar os cards
      
          // Concatenar o código do Card com os dados do JSON
          titulo = data.results[i].title;
          titulo_origi = data.results[i].original_title;
          lingua_origi = data.results[i].original_language;
          imagem = 'https://image.tmdb.org/t/p/w500' + data.results[i].poster_path;
          descricao = data.results[i].overview;
          id = data.results[i].id;
          lancamento = data.results[i].release_date;
          pop = data.results[i].popularity;
          av_glob = data.results[i].vote_average;

          codigo_html += `<div class="card mb-3" style="max-width: 700px;">
          <div class="row no-gutters">
            <div class="col-md-4">
              <img src="${imagem}" class="card-img" alt="${titulo}">
            </div>
            <div class="col-md-8">
              <div class="card-body">
                <h2 class="card-title">${titulo} (${lancamento})</h2>
                <h3 class="card-title">Título Original: ${titulo_origi}</br>Idioma Original: ${lingua_origi}</h3>
                <p class="card-text">Popularidade: ${pop}</p>
                <p class="card-text">Sinopse: ${descricao}</p>
                <p class="card-text">Avaliações: ${av_glob}</p>
                <a href="https://www.themoviedb.org/movie/${id}-${titulo}" target="_blank" id="buttonc1" class="btn btn-primary">Saiba Mais</a>
              </div>
            </div>
          </div>
        </div>`;
      
          
      // Repassar os cards para a página
      $('#pop').html(codigo_html);
      $("#titulo_session").html(titulo_html);
      
  });
}//end funcao Expandido( )

$(document).ready(function () {
  Expandido(sessionStorage.getItem("endp"),sessionStorage.getItem("id"));

  $("#btn_pesquisa").click(function () {
    //sessionStorage.setItem("isPesquisa", true);
    if (sessionStorage.getItem("isPesquisa")) {
      sessionStorage.setItem("item", $("#search").val());
    }
  });
  $("#onpopulares").click(function () {sessionStorage.setItem("pop", true);});
  $("#oncinema").click(function () {sessionStorage.setItem("cin", true);});
  $("#onnovi").click(function () {sessionStorage.setItem("novi", true);});
  sessionStorage.setItem("cin", false);
  sessionStorage.setItem("pop", false);
  sessionStorage.setItem("novi", false);
});
