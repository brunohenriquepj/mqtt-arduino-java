<#include "macros/base.ftl">

<#macro page_body>
    <#if idArea == 1 || idArea == 2>
        <div class="row">
            <div class="col l8 s12 offset-l2">
                <div class="section">
                    <h4>Área ${idArea}</h4>
                </div>
                <div class="divider"></div>
                <div class="section">
                    <ul class="collection">
                        <!-- início porta -->
                        <li class="collection-item avatar">
                            <div class="row">
                                <div class="col l12 s12">
                                    <div class="row">
                                        <div class="col l6 s3">
                                            <h5>Temperatura</h5>
                                            <p style="margin-top:10px; font-size:120%;">
                                                <i class="fa fa-thermometer-empty fa-5x"
                                                   aria-hidden="true"
                                                   id="temperatura-icone"></i>
                                            </p>
                                        </div>
                                        <div class="col l6 s9">
                                            <h2 style="margin-top:60px;">
                                                <span id="temperatura-estado">${temperaturaValor!"-"}</span> ºC
                                            </h2>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </li>
                        <!-- fim porta -->
                        <!-- início lampada 1 -->
                        <li class="collection-item avatar">
                            <div class="row">
                                <div class="col l12 s12">
                                    <div class="row">
                                        <div class="col l8 s8">
                                            <i class="fa fa-lightbulb-o circle <#if lampada1Estado == 1>yellow<#else>grey lighten-2</#if> black-text"
                                               id="lampada1-estado-icone"></i>
                                            <h5>Lâmpada 1</h5>
                                        </div>
                                        <div class="col l4 s4">
                                            <span class="badge <#if lampada1Estado == 1>yellow<#else>grey lighten-2</#if> black-text"
                                                  data-badge-caption=""
                                                  id="lampada1-estado-badge">
                                                <#if lampada1Estado == 1>
                                                    LIGADA
                                                <#else>
                                                    DESLIGADA
                                                </#if>
                                            </span>
                                        </div>
                                    </div>
                                </div>
                            </div>
                            <div class="row">
                                <div class="col l12 s12">
                                    <div class="row">
                                        <div class="col l4 s12">
                                            <div class="waves-effect waves-light btn" id="lampada1-estado-btn">
                                                <#if lampada1Estado == 1>
                                                    desligar
                                                    <#else>
                                                    ligar
                                                </#if>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </li>
                        <!-- fim lampada 1 -->
                        <!-- início lampada 2 -->
                        <li class="collection-item avatar">
                            <div class="row">
                                <div class="col l12 s12">
                                    <div class="row">
                                        <div class="col l8 s8">
                                            <i class="fa fa-lightbulb-o circle <#if lampada2Estado == 1>yellow<#else>grey lighten-2</#if> black-text"
                                               id="lampada2-estado-icone"></i>
                                            <h5>Lâmpada 2</h5>
                                        </div>
                                        <div class="col l4 s4">
                                            <span class="badge <#if lampada2Estado == 1>yellow<#else>grey lighten-2</#if> black-text"
                                                  data-badge-caption=""
                                                  id="lampada2-estado-badge">
                                                <#if lampada2Estado == 1>
                                                    LIGADA
                                                <#else>
                                                    DESLIGADA
                                                </#if>
                                            </span>
                                        </div>
                                    </div>
                                </div>
                            </div>
                            <div class="row">
                                <div class="col l12 s12">
                                    <div class="row">
                                        <div class="col l4 s12">
                                            <div class="waves-effect waves-light btn" id="lampada2-estado-btn">
                                                <#if lampada2Estado == 1>
                                                    desligar
                                                    <#else>
                                                    ligar
                                                </#if>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </li>
                        <!-- fim lampada 2 -->
                    </ul>
                </div>
            </div>
        </div>
    </#if>
    <script>
        idArea = "${idArea}";
    </script>
    <script type="text/javascript" src="/js/main.js"></script>
</#macro>

<@display_page/>
