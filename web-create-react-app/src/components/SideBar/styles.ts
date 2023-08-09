import styled from "styled-components";

export const Container = styled.form`
    background: #28a79b; 
    height: 100vh;
    display: flex;
    justify-content: center;
    padding: 0rem 1rem;
    border-right: 0.1rem solid white;
    width: 15rem;

    span {
        color: white;
    }

    ul {
        list-style:none;

        li{
            margin-bottom: 0.5rem;

            input {
                border-radius: 0.25rem;
                border: 1px dotted #d7d7d7;
                
                &::placeholder {
                    color: #DDDDDD;
                    padding-left: 0.5rem;
                }
            }

            button {
                width:100%;
                margin-top: 1.7rem;
                background: white;
                color: #484d50;
                border-radius: 0.25rem;
                border: 0;
                padding: 0.25rem 0rem;

                transition: filter 0.2s;
                &:hover {
                    filter: brightness(0.7);
                }
            }
        }

        .buttonPagesStyle {
            margin-top: 5rem;

            button {
                background: #FFFDD0;
                height: 3rem;
            }
        }
        
    }

`;