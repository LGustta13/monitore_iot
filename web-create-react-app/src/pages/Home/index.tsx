import { Container } from "./styles";

// Componentes
import { Sidebar } from "../../components/SideBar";
import { Header } from "../../components/Header";
import { Footer } from "../../components/Footer";
import { Dashboard } from "../../components/Dashboard";
import { Graph } from "../../components/Graph";

import { useState } from "react";

type searchProps = {
    chave: string,
    dataInicial: string,
    dataFinal: string
}

export function Home() {

    const [search, setSearch] = useState<searchProps>({
        chave: "",
        dataInicial: "",
        dataFinal: ""
    });

    function createSearch(props: searchProps) {
        setSearch(props);
    }

    return (
        <Container>

            <Sidebar searchInput={createSearch} />

            <div className="homeStyle">
                <Header />
                {/* <Graph handleSearch={search} /> */}
                <Dashboard handleSearch={search} />
            </div>

            <Footer />

        </Container>
    );
}