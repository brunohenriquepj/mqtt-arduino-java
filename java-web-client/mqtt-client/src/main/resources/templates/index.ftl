<#include "macros/base.ftl">

<#macro page_body>
    <div class="row">
        <div class="col l12 s12">
            <div class="row">
                <div class="col s12 l8 offset-l2">
                    <h1 style="margin-top:20px;">Seja Bem-vindo!</h1>
                </div>
            </div>

            <div class="row">
                <div class="col s12 l8 offset-l2">
                    <p style="margin-top:50px;">
                        <h3>Selecione uma área abaixo: </h3>
                    </p>
                </div>
            </div>

            <div class="row">
                <a href="/area/1" class="col s12 l6 offset-l3 card-panel blue-grey darken-2 white-text waves-effect waves-grey hoverable"
                   style="padding:10px; margin-bottom:-5px;">
                    <div class="center-align">
                        <h4>Área 1</h4>
                    </div>
                </a>
            </div>

            <div class="row">
                <a href="/area/2" class="col s12 l6 offset-l3 card-panel blue-grey darken-2 white-text waves-effect waves-grey hoverable" style="padding:10px;">
                    <div class="center-align">
                        <h4>Área 2</h4>
                    </div>
                </a>
            </div>
        </div>
    </div>
    <script>
        var idArea = null;
    </script>
    <script type="text/javascript" src="/js/main.js"></script>
</#macro>

<@display_page/>