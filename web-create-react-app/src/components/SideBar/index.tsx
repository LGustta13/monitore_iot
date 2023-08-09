import { FiAlignJustify } from "react-icons/fi";
import { Container } from "./styles";
import { FormEvent, useState } from "react";

type searchProps = {
    chave: string,
    dataInicial: string,
    dataFinal: string
}

type searchInputProps = {
    searchInput: (search: searchProps) => void
}

export function Sidebar({ searchInput }: searchInputProps) {

    const [chave, setChave] = useState("");
    const [dataInicial, setDataInicial] = useState("");
    const [dataFinal, setDataFinal] = useState("");

    function handleNewSearch(event: FormEvent) {
        event.preventDefault();

        searchInput({
            chave, dataInicial, dataFinal
        })

        setChave("");
        setDataInicial("");
        setDataFinal("");
    }

    return (
        <Container onSubmit={handleNewSearch}>
            <nav>
                <FiAlignJustify />
                <ul>
                    <li>
                        <div>
                            <span>Chave de Acesso</span>
                        </div>
                        <input
                            placeholder="chave"
                            value={chave}
                            onChange={event => setChave(event.target.value)}
                        />
                    </li>
                    <li>
                        <div>
                            <span>Data Inicial</span>
                        </div>
                        <input
                            placeholder="data"
                            value={dataInicial}
                            onChange={event => setDataInicial(event.target.value)}
                        />
                    </li>
                    <li>
                        <div>
                            <span>Data Final</span>
                        </div>
                        <input
                            placeholder="data"
                            value={dataFinal}
                            onChange={event => setDataFinal(event.target.value)}
                        />
                    </li>
                    <li>
                        <button type="submit">
                            Buscar
                        </button>
                    </li>
                    <li>
                        <button style={{ background: "#F08080" }}>
                            Resetar busca
                        </button>
                    </li>
                    <div className="buttonPagesStyle">
                        <li>
                            <button>
                                Abastecimentos
                            </button>
                        </li>
                        <li>
                            <button>
                                Dashboards
                            </button>
                        </li>
                    </div>

                </ul>
            </nav>
        </Container>

    );
}