<#import "/spring.ftl" as spring />
<#macro display_navbar>
    <header>
    <nav>
        <div class="nav-wrapper cyan darken-2">
            <a href="/" class="brand-logo center">ArduinoMQTT</a>
            <a href="#" data-activates="slide-out" class="button-collapse"><i class="fa fa-bars fa-2x"></i></a>
        </div>
    </nav>

    <ul id="slide-out" class="side-nav fixed z-depth-5" style="transform: translateX(0px);">
        <li>
            <div class="userView">
                <div class="background">
                    <img src="/images/backgrounds/background.png" width="100%" height="100%">
                </div>
                <i class="fa fa-user-circle-o fa-3x fa-inverse"></i>
                <a href="#!name"><span class="white-text name">User</span></a>
                <a href="#!email"><span class="white-text email">user@email.com</span></a>
            </div>
        </li>
        <li class="<#if idArea == 1>active grey lighten-3</#if>">
            <a href="/area/1" class="waves-effect waves-grey hoverable">
                <i class="fa fa-tasks fa-2x"></i>
                Área 1
            </a>
        </li>
        <li class="<#if idArea == 2>active grey lighten-3</#if>">
            <a href="/area/2" class="waves-effect waves-grey hoverable">
                <i class="fa fa-tasks fa-2x"></i>
                Área 2
            </a>
        </li>
    </ul>
    </header>
</#macro>