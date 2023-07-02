import { api } from '@/libs/api'

type suppliesProps = {

}

export default async function Home() {

  const response = await api.get('/vehicles')

  return (
    <main className="flex min-h-screen flex-col items-center justify-between p-24">
      {

      }
    </main>
  )
}
